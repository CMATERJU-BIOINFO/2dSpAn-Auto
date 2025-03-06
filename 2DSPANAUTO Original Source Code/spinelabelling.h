#ifndef SPINELABELLING_H
#define SPINELABELLING_H
#include "matrix.h"
#include "label.h"

#include <QPoint>
#include <QQueue>
template <typename T>
class SpineLabelling
{
public:
    SpineLabelling() {}

    static Matrix<T> primarySegmentation(const Matrix<T> originalSkeleton,const Matrix<T> dendriteSkel){
        int r=dendriteSkel.getRows(),c=dendriteSkel.getCols();
        Matrix<T> combinedSkel(r,c,0);
        for(int j=1;j<c-1;j++)
        {
            for(int i=1;i<r-1;i++)
            {
                int val=dendriteSkel.at(i,j).getValue();
                if(val){
                    if(val==255)
                        combinedSkel.at(i,j).setValue(__dendrite__);
                    else if (val==__jp__) {
                        combinedSkel.at(i,j).setValue(__jp__);
                    }
                }
                else {
                    combinedSkel.at(i,j).setValue(originalSkeleton.at(i,j).getValue()?__spine__:0);
                }
            }
        }
        for(int j=1;j<c-1;j++)
        {
            for(int i=1;i<r-1;i++)
            {
                int val=combinedSkel.at(i,j).getValue();
                if(val==__spine__){
                    Neighborhood<T> n=combinedSkel.getNeighborhood(i,j);
                    QVector<const Cell<T>*> nb=n.getAllNeighbors();
                    int count=0;
                    foreach (auto e, nb) {
                        if(e->getValue()>0)
                            count++;
                    }
                    if(     count==1 || isSpineEnd( n.getNeighborsBinaryNot(0) )      )
                        combinedSkel.at(i,j).setValue(__ep__);

                }
                else if(val==__dendrite__){
                    Neighborhood<T> n=combinedSkel.getNeighborhood(i,j);
                    std::bitset<8> nb=n.getNeighborsBinary(__spine__);
                    if(nb.any())
                        combinedSkel.at(i,j).setValue(__jp__);
                }
            }
        }

        return combinedSkel;
    }

    static Matrix<T> finalSegmentation(const Matrix<T> primary){
        Matrix<T> copy(primary);
        detectDDE(primary,copy);
        detectDDJ(primary,copy);
        detectSSJ(primary,copy);
        detectSSE(primary,copy);
        adjustDoubleBluePoints(copy);
        adjustJunctions(copy);
        return copy;
    }


private:
    inline static bool isSpineEnd(std::bitset<8> neighborhood){
        QString nb=QString::fromStdString(neighborhood.to_string());
        QStringList patternlist={
            "11000000",
            "01100000",
            "00110000",
            "00011000",
            "00001100",
            "00000110",
            "00000011",
            "10000001",
        };
        foreach (auto e, patternlist) {
            if(nb==e)
                return true;
        }
        return false;
    }
    inline static void detectDDE(const Matrix<T> marked, Matrix<T> &skel){
        int r=marked.getRows(),c=marked.getCols();
        for(int j=1;j<c-1;j++){
            for(int i=1;i<r-1;i++){
                int val=marked.at(i,j).getValue();
                if(val==__jp__ || val==__ep__ || val==__dendrite__)
                {
                    Neighborhood<T> n=marked.getNeighborhood(i,j);
                    std::bitset<8> nbDen=n.getNeighborsBinary(__dendrite__),
                        nbJP=n.getNeighborsBinary(__jp__);
                    std::bitset<8> result = nbDen | nbJP;
                    if(result.count()==1)
                        skel.at(i,j).setValue(__jp__);
                }
            }
        }
    }
    inline static void detectDDJ(const Matrix<T> marked, Matrix<T> &skel){
        int r=marked.getRows(),c=marked.getCols();
        for(int j=1;j<c-1;j++){
            for(int i=1;i<r-1;i++){
                int val=marked.at(i,j).getValue();
                if(val==__jp__)
                {
                    Neighborhood<T> n=marked.getNeighborhood(i,j);
                    std::bitset<8> nbDen=n.getNeighborsBinary(__dendrite__),
                        nbJP=n.getNeighborsBinary(__jp__);
                    std::bitset<8> result = nbDen | nbJP;
                    if(result.count()>=3)
                        skel.at(i,j).setValue(__ddj__);
                }
            }
        }
    }
    inline static void detectSSJ(const Matrix<T> marked, Matrix<T> &skel){
        int r=marked.getRows(),c=marked.getCols();
        for(int j=1;j<c-1;j++){
            for(int i=1;i<r-1;i++){
                int val=marked.at(i,j).getValue();
                if(val==__spine__)
                {
                    Neighborhood<T> n=marked.getNeighborhood(i,j);
                    std::bitset<8> nbSpine=n.getNeighborsBinary(__spine__),
                        nbEP=n.getNeighborsBinary(__ep__);
                    std::bitset<8> result = nbSpine | nbEP;
                    if(result.count()>=3)
                    {
                        skel.at(i,j).setValue(__ssj__);
                    }
                    else if(result.count()==2){

                        if (marked.at(i + 1, j).getValue() == __spine__ || marked.at(i + 1, j).getValue() == __ep__) {
                            if (marked.at(i, j + 1).getValue() == __spine__ || marked.at(i, j + 1).getValue() == __ep__ ||
                                marked.at(i, j - 1).getValue() == __spine__ || marked.at(i, j - 1).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }

                        if (marked.at(i - 1, j).getValue() == __spine__ || marked.at(i - 1, j).getValue() == __ep__) {
                            if (marked.at(i, j + 1).getValue() == __spine__ || marked.at(i, j + 1).getValue() == __ep__ ||
                                marked.at(i, j - 1).getValue() == __spine__ || marked.at(i, j - 1).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }

                        if (marked.at(i, j + 1).getValue() == __spine__ || marked.at(i, j + 1).getValue() == __ep__) {
                            if (marked.at(i + 1, j).getValue() == __spine__ || marked.at(i + 1, j).getValue() ==__ep__ ||
                                marked.at(i - 1, j).getValue() == __spine__ || marked.at(i - 1, j).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }

                        if (marked.at(i, j - 1).getValue() == __spine__ || marked.at(i, j - 1).getValue() == __ep__) {
                            if (marked.at(i + 1, j).getValue() == __spine__ || marked.at(i + 1, j).getValue() == __ep__ ||
                                marked.at(i - 1, j).getValue() == __spine__ || marked.at(i - 1, j).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }


                        if (marked.at(i + 1, j - 1).getValue() == __spine__ || marked.at(i + 1, j - 1).getValue() == __ep__) {
                            if (marked.at(i - 1, j - 1).getValue() == __spine__ || marked.at(i - 1, j - 1).getValue() == __ep__ ||
                                marked.at(i + 1, j + 1).getValue() == __spine__ || marked.at(i + 1, j + 1).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }

                        if (marked.at(i - 1, j + 1).getValue() == __spine__ || marked.at(i - 1, j + 1).getValue() == __ep__) {
                            if (marked.at(i + 1, j + 1).getValue() == __spine__ || marked.at(i + 1, j + 1).getValue() == __ep__ ||
                                marked.at(i - 1, j - 1).getValue() == __spine__ || marked.at(i - 1, j - 1).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }

                        if (marked.at(i + 1, j + 1).getValue() == __spine__ || marked.at(i + 1, j + 1).getValue() == __ep__) {
                            if (marked.at(i - 1, j + 1).getValue() == __spine__ || marked.at(i - 1, j + 1).getValue() == __ep__ ||
                                marked.at(i + 1, j - 1).getValue() == __spine__ || marked.at(i + 1, j - 1).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }

                        if (marked.at(i - 1, j - 1).getValue() == __spine__ || marked.at(i - 1, j - 1).getValue() == __ep__) {
                            if (marked.at(i + 1, j - 1).getValue() == __spine__ || marked.at(i + 1, j - 1).getValue() == __ep__ ||
                                marked.at(i - 1, j + 1).getValue() == __spine__ || marked.at(i - 1, j + 1).getValue() == __ep__) {
                                std::bitset<8> nbJP = n.getNeighborsBinary(__jp__), nbDDJ = n.getNeighborsBinary(__ddj__);
                                std::bitset<8> result = nbJP | nbDDJ;
                                if (result.any())
                                    skel.at(i, j).setValue(__ssj__);
                            }
                        }

                    }

                }
            }
        }

        for(int j=1;j<c-1;j++){
            for(int i=1;i<r-1;i++){
                if(skel.at(i, j).getValue() == __spine__)
                {

                    if(skel.at(i - 1, j).getValue() == __ssj__ && skel.at(i, j + 1).getValue() == __ssj__)
                    {
                        skel.at(i - 1, j).setValue(__spine__);
                        skel.at(i, j + 1).setValue(__spine__);
                        skel.at(i, j).setValue(__ssj__);
                    }

                    if(skel.at(i + 1, j).getValue() == __ssj__ && skel.at(i, j + 1).getValue() == __ssj__)
                    {
                        skel.at(i + 1, j).setValue(__spine__);
                        skel.at(i, j + 1).setValue(__spine__);
                        skel.at(i, j).setValue(__ssj__);
                    }

                    if(skel.at(i - 1, j).getValue() == __ssj__ && skel.at(i, j - 1).getValue() == __ssj__)
                    {
                        skel.at(i - 1, j).setValue(__spine__);
                        skel.at(i, j - 1).setValue(__spine__);
                        skel.at(i, j).setValue(__ssj__);
                    }

                    if(skel.at(i + 1, j).getValue() == __ssj__ && skel.at(i, j - 1).getValue() == __ssj__)
                    {
                        skel.at(i + 1, j).setValue(__spine__);
                        skel.at(i, j - 1).setValue(__spine__);
                        skel.at(i, j).setValue(__ssj__);
                    }
                }

            }
        }

    }
    inline static void detectSSE(const Matrix<T> marked, Matrix<T> &skel){
        int r=marked.getRows(),c=marked.getCols();
        for(int j=1;j<c-1;j++){
            for(int i=1;i<r-1;i++){
                if(marked.at(i,j).getValue()==__ep__){
                    skel.at(i,j).setValue(__sse__);
                }
            }
        }
    }
    inline static void adjustDoubleBluePoints(Matrix<T> &combinedSkel){
        int r=combinedSkel.getRows(),c=combinedSkel.getCols();
        for(int j = 1; j < c-1; j++)
        {
            for(int i = 1; i < r-1; i++)
            {
                if(combinedSkel.at(i, j).getValue() == __jp__ && combinedSkel.at(i + 1, j).getValue() == __jp__) {
                    bool center = false;
                    bool right = false;
                    bool flag = false;
                    for (int x = -1; x < 1; ++x) {
                        for (int y = -1; y < 2; ++y) {
                            T val=combinedSkel.at(i+x,j+y).getValue();
                            if (val == __spine__ || val ==__ssj__ ||val ==__sse__) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            center = true;
                            break;
                        }
                    }
                    flag = false;
                    for (int x = 0; x < 2; ++x) {
                        for (int y = -1; y < 2; ++y) {
                            T val=combinedSkel.at(i+1+x,j+y).getValue();
                            if (val == __spine__ || val ==__ssj__ ||val ==__sse__) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            right = true;
                            break;
                        }
                    }
                    if(center && !right) {
                        combinedSkel.at(i + 1, j).setValue(__dendrite__);
                    } else if(!center && right) {
                        combinedSkel.at(i, j).setValue(__dendrite__);
                    }
                }

                else if (combinedSkel.at(i, j).getValue() == __jp__ && combinedSkel.at(i, j + 1).getValue() == __jp__) {
                    bool center = false;
                    bool down = false;
                    bool flag = false;

                    for (int x = -1; x < 2; ++x) {
                        for (int y = -1; y < 1; ++y) {
                            T val=combinedSkel.at(i+x,j+y).getValue();
                            if (val == __spine__ || val ==__ssj__ ||val ==__sse__) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            center = true;
                            break;
                        }
                    }
                    flag = false;
                    for (int x = -1; x < 2; ++x) {
                        for (int y = 0; y < 2; ++y) {
                            T val=combinedSkel.at(i+x,j+1+y).getValue();
                            if (val == __spine__ || val ==__ssj__ ||val ==__sse__) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            down = true;
                            break;
                        }
                    }
                    if (center && !down) {
                        combinedSkel.at(i, j + 1).setValue(__dendrite__);
                    } else if (!center && down) {
                        combinedSkel.at(i, j).setValue(__dendrite__);
                    }
                }


            }
        }

    }
    inline static void adjustJunctions(Matrix<T> &skel1){
        int r=skel1.getRows(),c=skel1.getCols();
        for(int j = 1; j < c-1; j++)
        {
            for(int i = 1; i < r-1; i++)
            {
                if(skel1.at(i, j).getValue() == __ssj__ || skel1.at(i , j).getValue() == __ddj__){
                    if(skel1.at(i, j).getValue() == __ssj__) {

                        if(skel1.at(i + 1, j).getValue() == __ssj__) {
                            if(skel1.at(i + 1, j - 1).getValue() == __ssj__ && skel1.at(i, j + 1).getValue() == __ssj__) {
                                skel1.at(i + 1, j - 1).setValue(__spine__);
                                skel1.at(i, j + 1).setValue(__spine__);
                            }
                            if(skel1.at(i, j - 1).getValue() == __ssj__ && skel1.at(i + 1, j + 1).getValue() == __ssj__) {
                                skel1.at(i, j - 1).setValue(__spine__);
                                skel1.at(i + 1, j + 1).setValue(__spine__);
                            }
                        }

                        if(skel1.at(i - 1, j).getValue() == __ssj__) {
                            if(skel1.at(i - 1, j - 1).getValue() == __ssj__ && skel1.at(i, j + 1).getValue() == __ssj__) {
                                skel1.at(i - 1, j - 1).setValue(__spine__);
                                skel1.at(i, j + 1).setValue(__spine__);
                            }
                            if(skel1.at(i - 1, j + 1).getValue() == __ssj__ && skel1.at(i, j - 1).getValue() == __ssj__) {
                                skel1.at(i - 1, j + 1).setValue(__spine__);
                                skel1.at(i, j - 1).setValue(__spine__);
                            }
                        }


                        if(skel1.at(i, j + 1).getValue() == __ssj__) {
                            if(skel1.at(i - 1, j + 1).getValue() == __ssj__ && skel1.at(i + 1, j).getValue() == __ssj__) {
                                skel1.at(i - 1, j + 1).setValue(__spine__);
                                skel1.at(i + 1, j).setValue(__spine__);
                            }
                            if(skel1.at(i + 1, j + 1).getValue() == __ssj__ && skel1.at(i - 1, j).getValue() == __ssj__) {
                                skel1.at(i + 1, j + 1).setValue(__spine__);
                                skel1.at(i - 1, j).setValue(__spine__);
                            }
                        }


                        if(skel1.at(i, j - 1).getValue() == __ssj__) {
                            if(skel1.at(i - 1, j - 1).getValue() == __ssj__ && skel1.at(i + 1, j).getValue() == __ssj__) {
                                skel1.at(i - 1, j - 1).setValue(__spine__);
                                skel1.at(i + 1, j).setValue(__spine__);
                            }
                            if(skel1.at(i + 1, j - 1).getValue() == __ssj__ && skel1.at(i - 1, j).getValue() == __ssj__) {
                                skel1.at(i + 1, j - 1).setValue(__spine__);
                                skel1.at(i - 1, j).setValue(__spine__);
                            }
                        }


                        if(skel1.at(i - 1, j).getValue() == __ssj__ && skel1.at(i, j + 1).getValue() == __ssj__) {
                            skel1.at(i - 1, j).setValue(__spine__);
                            skel1.at(i, j + 1).setValue(__spine__);
                        }

                        if(skel1.at(i + 1, j).getValue() == __ssj__ && skel1.at(i, j + 1).getValue() == __ssj__) {
                            skel1.at(i + 1, j).setValue(__spine__);
                            skel1.at(i, j + 1).setValue(__spine__);
                        }

                        if(skel1.at(i - 1, j).getValue() == __ssj__ && skel1.at(i, j - 1).getValue() == __ssj__) {
                            skel1.at(i - 1, j).setValue(__spine__);
                            skel1.at(i, j - 1).setValue(__spine__);
                        }

                        if(skel1.at(i + 1, j).getValue() == __ssj__ && skel1.at(i, j - 1).getValue() == __ssj__) {
                            skel1.at(i + 1, j).setValue(__spine__);
                            skel1.at(i, j - 1).setValue(__spine__);
                        }
                    }
                    else if(skel1.at(i, j).getValue() == __ddj__ || skel1.at(i, j).getValue() == __jp__) {
                        if((skel1.at(i - 1, j).getValue() == __jp__ || skel1.at(i - 1, j).getValue() == __ddj__) &&
                            (skel1.at(i, j + 1).getValue() == __ddj__ || skel1.at(i, j + 1).getValue() == __jp__)) {
                            skel1.at(i - 1, j).setValue(__dendrite__);
                            skel1.at(i, j + 1).setValue(__dendrite__);
                        }

                        if((skel1.at(i + 1, j).getValue() == __jp__ || skel1.at(i + 1, j).getValue() == __ddj__) &&
                            (skel1.at(i, j + 1).getValue() == __jp__ || skel1.at(i, j + 1).getValue() == __ddj__)) {
                            skel1.at(i + 1, j).setValue(__dendrite__);
                            skel1.at(i, j + 1).setValue(__dendrite__);
                        }

                        if((skel1.at(i - 1, j).getValue() == __ddj__ || skel1.at(i - 1, j).getValue() == __jp__) &&
                            (skel1.at(i, j - 1).getValue() == __ddj__ || skel1.at(i, j - 1).getValue() == __jp__)) {
                            skel1.at(i - 1, j).setValue(__dendrite__);
                            skel1.at(i, j - 1).setValue(__dendrite__);
                        }

                        if((skel1.at(i + 1, j).getValue() == __ddj__ || skel1.at(i + 1, j).getValue() == __jp__) &&
                            (skel1.at(i, j - 1).getValue() == __ddj__ || skel1.at(i, j - 1).getValue() == __jp__)) {
                            skel1.at(i + 1, j).setValue(__dendrite__);
                            skel1.at(i, j - 1).setValue(__dendrite__);
                        }
                    }

                }
            }
        }
    }

};
#endif
