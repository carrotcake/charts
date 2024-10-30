#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>

class ScoreWidget : public QWidget {
    Q_OBJECT
public:
    explicit ScoreWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
signals:
};

#endif // SCOREWIDGET_H
