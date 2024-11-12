#ifndef MEASURE_H
#define MEASURE_H

#include <QObject>

class Measure : public QObject {
    Q_OBJECT
public:
    explicit Measure(QObject *parent = nullptr);

signals:
};

#endif // MEASURE_H
