// savehandler.cpp
#include "savehandler.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

SaveHandler::SaveHandler(const QVector<SpineStats>& tableData, double res)
    : table(tableData), resolution(res) {}

QString SaveHandler::getFilePath(const QString& originalPath, bool inMicrometers) const {
    QFileInfo fileInfo(originalPath);
    QString baseName = fileInfo.completeBaseName();
    QString suffix = fileInfo.suffix();
    QString unit = inMicrometers ? "_micrometers" : "_pixels";
    return fileInfo.path() + "/" + baseName + unit + "." + suffix;
}

QVector<SpineStats> SaveHandler::filterByType(int type) const {
    QVector<SpineStats> filtered;
    for (const auto& stat : table) {
        if (stat.type == type) {
            filtered.push_back(stat);
        }
    }
    return filtered;
}

QString SaveHandler::computeTypeStats(const QVector<SpineStats>& stats, const QString& typeName, bool inMicrometers) {
    if (stats.isEmpty()) return QString();

    QString statsText = QString("%1 Spine Statistics\n").arg(typeName);
    QString unit = inMicrometers ? "µm" : "pixels";
    QString area_unit = inMicrometers ? "µm²" : "pixels²";

    struct StatAttribute {
        QString name;
        QString unit;
        std::function<double(const SpineStats&)> getter;
    };

    std::vector<StatAttribute> attributes = {
        {"Head Width", unit, [&](const SpineStats& s) {
             return inMicrometers ? s.headWidth * resolution : s.headWidth; }},
        {"Neck Length", unit, [&](const SpineStats& s) {
             return inMicrometers ? s.neckLength * resolution : s.neckLength; }},
        {"Spine Length", unit, [&](const SpineStats& s) {
             return inMicrometers ? s.spineLength * resolution : s.spineLength; }},
        {"Avg Neck Width", unit, [&](const SpineStats& s) {
             return inMicrometers ? s.avgNeckWidth * resolution : s.avgNeckWidth; }},
        {"Area", area_unit, [&](const SpineStats& s) {
             return inMicrometers ? s.area * resolution * resolution : s.area; }}
    };

    for (const auto& attr : attributes) {
        double mean = SpineStats::mean(stats, attr.getter);
        double stddev = SpineStats::stddev(stats, attr.getter);
        statsText += QString("%1 (%2),Mean,%3,StdDev,%4\n")
                         .arg(attr.name)
                         .arg(attr.unit)
                         .arg(mean, 0, 'f', 2)
                         .arg(stddev, 0, 'f', 2);
    }
    return statsText;
}

bool SaveHandler::saveNet(const QString& filepath) {
    // Save pixel measurements
    bool pixelSuccess = [&]() {
        QFile file(getFilePath(filepath, false));
        if (!file.open(QIODevice::WriteOnly)) return false;
        QTextStream out(&file);

        out << "Overall Spine Statistics (Pixels)\n";
        out << QString("Total Spines,%1\n").arg(table.size());

        auto filoSpines = filterByType(__filopodium__);
        auto stubbySpines = filterByType(__stubby__);
        auto mushroomSpines = filterByType(__mushroom__);

        out << QString("Type Distribution,Filopodia,%1,Stubby,%2,Mushroom,%3\n\n")
                   .arg(filoSpines.size())
                   .arg(stubbySpines.size())
                   .arg(mushroomSpines.size());

        out << computeTypeStats(filoSpines, "Filopodia", false) << "\n";
        out << computeTypeStats(stubbySpines, "Stubby", false) << "\n";
        out << computeTypeStats(mushroomSpines, "Mushroom", false);

        file.close();
        return true;
    }();

    // Save micrometer measurements
    bool microSuccess = [&]() {
        QFile file(getFilePath(filepath, true));
        if (!file.open(QIODevice::WriteOnly)) return false;
        QTextStream out(&file);

        out << "Overall Spine Statistics (Micrometers)\n";
        out << QString("Total Spines,%1\n").arg(table.size());

        auto filoSpines = filterByType(__filopodium__);
        auto stubbySpines = filterByType(__stubby__);
        auto mushroomSpines = filterByType(__mushroom__);

        out << QString("Type Distribution,Filopodia,%1,Stubby,%2,Mushroom,%3\n\n")
                   .arg(filoSpines.size())
                   .arg(stubbySpines.size())
                   .arg(mushroomSpines.size());

        out << computeTypeStats(filoSpines, "Filopodia", true) << "\n";
        out << computeTypeStats(stubbySpines, "Stubby", true) << "\n";
        out << computeTypeStats(mushroomSpines, "Mushroom", true);

        file.close();
        return true;
    }();

    return pixelSuccess && microSuccess;
}

bool SaveHandler::saveAllIndividual(const QString& filepath) {
    // Save pixel measurements
    bool pixelSuccess = [&]() {
        QFile file(getFilePath(filepath, false));
        if (!file.open(QIODevice::WriteOnly)) return false;
        QTextStream out(&file);

        out << "Spine Index,Type,SBP X,SBP Y,Head Width (pixels),Neck Length (pixels),";
        out << "Spine Length (pixels),Avg Neck Width (pixels),Min Neck Width (pixels),";
        out << "Max Neck Width (pixels),Area (pixels²)\n";

        for (int i = 0; i < table.size(); ++i) {
            const auto& spine = table[i];
            QString type = spine.type == __filopodium__ ? "Filopodia" :
                               spine.type == __stubby__ ? "Stubby" : "Mushroom";

            out << QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11\n")
                       .arg(i)
                       .arg(type)
                       .arg(spine.sbp.x())
                       .arg(spine.sbp.y())
                       .arg(spine.headWidth)
                       .arg(spine.neckLength)
                       .arg(spine.spineLength)
                       .arg(spine.avgNeckWidth, 0, 'f', 2)
                       .arg(spine.minNeckWidth)
                       .arg(spine.maxNeckWidth)
                       .arg(spine.area);
        }
        file.close();
        return true;
    }();

    // Save micrometer measurements
    bool microSuccess = [&]() {
        QFile file(getFilePath(filepath, true));
        if (!file.open(QIODevice::WriteOnly)) return false;
        QTextStream out(&file);

        out << "Spine Index,Type,SBP X,SBP Y,Head Width (µm),Neck Length (µm),";
        out << "Spine Length (µm),Avg Neck Width (µm),Min Neck Width (µm),";
        out << "Max Neck Width (µm),Area (µm²)\n";

        for (int i = 0; i < table.size(); ++i) {
            const auto& spine = table[i];
            QString type = spine.type == __filopodium__ ? "Filopodia" :
                               spine.type == __stubby__ ? "Stubby" : "Mushroom";

            out << QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11\n")
                       .arg(i)
                       .arg(type)
                       .arg(spine.sbp.x())
                       .arg(spine.sbp.y())
                       .arg(spine.headWidth * resolution, 0, 'f', 2)
                       .arg(spine.neckLength * resolution, 0, 'f', 2)
                       .arg(spine.spineLength * resolution, 0, 'f', 2)
                       .arg(spine.avgNeckWidth * resolution, 0, 'f', 2)
                       .arg(spine.minNeckWidth * resolution, 0, 'f', 2)
                       .arg(spine.maxNeckWidth * resolution, 0, 'f', 2)
                       .arg(spine.area * resolution * resolution, 0, 'f', 2);
        }
        file.close();
        return true;
    }();

    return pixelSuccess && microSuccess;
}
