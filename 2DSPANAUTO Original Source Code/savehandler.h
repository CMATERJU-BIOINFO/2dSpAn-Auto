// savehandler.h
#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H
#include <QVector>
#include <QString>
#include "analysis.h"

class SaveHandler {
public:
    SaveHandler(const QVector<SpineStats>& tableData, double resolution);
    bool saveNet(const QString& filepath);
    bool saveAllIndividual(const QString& filepath);

private:
    QVector<SpineStats> table;
    double resolution;

    // Helper methods
    QString computeTypeStats(const QVector<SpineStats>& stats, const QString& typeName, bool inMicrometers);
    QVector<SpineStats> filterByType(int type) const;
    QString getFilePath(const QString& originalPath, bool inMicrometers) const;
};
#endif // SAVEHANDLER_H
