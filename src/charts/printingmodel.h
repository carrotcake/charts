#ifndef PRINTINGMODEL_H
#define PRINTINGMODEL_H

#include <QObject>

class PrintingModel : public QObject {
    Q_OBJECT
public:
    explicit PrintingModel(QObject *parent = nullptr);

signals:
};

#endif // PRINTINGMODEL_H
