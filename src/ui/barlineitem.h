#pragma once

#include <QGraphicsLineItem>

class BarlineItem : public QGraphicsLineItem {
public:
    BarlineItem(size_t measure);

private:
    size_t m_measure;
};
