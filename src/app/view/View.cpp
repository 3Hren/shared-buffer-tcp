#include "View.h"

#include <QHeaderView>

View::View(QWidget *parent) :
    QTableView(parent)
{
    horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);    
}
