﻿#include "dropgraphicsview.h"
#include <QtWidgets>
#include "chip.h"

#define INTERVAL		34	//
#define RECT_INTERVAL	12	//
#define RECTWIDTH		22	//
#define RECTHEIGHT		10	//
#define LEFTRECT		4	//
#define SMALL_INTERVAL	5	//鼠标改变形状的那个区域的偏移量
#define FONT_SIZE		8	//
#define FONT_Y_OFFSET	7	//

DropGraphicsView::DropGraphicsView(QWidget *parent) : QGraphicsView(parent), m_zoomFactor(0)
{
    setAcceptDrops(true);
    m_scene = new DropGraphicsScene();
    setScene(m_scene);

    setCacheMode(CacheNone);
    setDragMode(QGraphicsView::NoDrag);
    setMouseTracking (true);
    setAlignment(Qt::AlignLeft|Qt::AlignTop);
}

void DropGraphicsView::setZoomFactor(int factor)
{
    if(m_zoomFactor > 250)
        m_zoomFactor = 250;
    if(m_zoomFactor < -250)
        m_zoomFactor = -250;

    m_zoomFactor = factor;
    setupMatrix();
}

void DropGraphicsView::resizeEvent(QResizeEvent *event)
{
    setSceneRect(-width()/2, -height()/2, width()/2, height()/2);
}

void DropGraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            zoomIn(5);
        else
            zoomOut(5);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

void DropGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void DropGraphicsView::setupMatrix()
{
    qreal scale = qPow(qreal(2), (m_zoomFactor) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);
    setMatrix(matrix);
}

void DropGraphicsView::zoomIn(int level)
{
    m_zoomFactor += level;
    if(m_zoomFactor > 250)
        m_zoomFactor = 250;

    setupMatrix();
    emit zoom(m_zoomFactor);
}

void DropGraphicsView::zoomOut(int level)
{
    m_zoomFactor -= level;
    if(m_zoomFactor < -250)
        m_zoomFactor = -250;

    setupMatrix();
    emit zoom(m_zoomFactor);
}



DropGraphicsScene::DropGraphicsScene(QWidget *parent) : QGraphicsScene(parent),
    m_curFrame(nullptr), is_drag(false), is_move(false)
{
    SetMouseMenu();
}

void DropGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void DropGraphicsScene::SetMouseMenu()
{
    QAction *deleteAction = new QAction(QIcon(":/Resources/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    QAction *modifyAction = new QAction(QIcon(":/Resources/modify.png"), tr("&Modify"), this);
    modifyAction->setShortcut(tr("Modify"));
    modifyAction->setStatusTip(tr("Modify item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(slot_deleteItem()));
    connect(modifyAction, SIGNAL(triggered()), this, SLOT(slot_modifyItem()));
    myItemMenu = new QMenu("&Item");
    myItemMenu->addAction(deleteAction);
    myItemMenu->addAction(modifyAction);
}

void DropGraphicsScene::slot_deleteItem()
{
    //    QList<QGraphicsItem *> items = selectedItems();
    //    QPointF point;
    //    int count = items.count();
    //    Frame *frame = (Frame *)items.at(count - 1);
    //    emit deleteFrame(frame);
    //    for (int i = 0; i < count; i++)
    //    {
    //        QGraphicsItem *item = items.at(i);
    //        point = item->scenePos();
    //        removeItem(item);
    //    }
}

void DropGraphicsScene::DeleteItem()
{
    //    QList<QGraphicsItem *> items = selectedItems();
    //    QPointF point;
    //    int count = items.count();
    //    Frame *frame = (Frame *)items.at(count - 1);
    //    emit deleteFrame(frame);
    //    for (int i = 0; i < count; i++)
    //    {
    //        QGraphicsItem *item = items.at(i);
    //        point = item->scenePos();
    //        removeItem(item);
    //    }
}

void DropGraphicsScene::slot_modifyItem()
{
    //    optionDlg = new OptionDlg();
    //    connect(optionDlg->ui.pushButton_ok, SIGNAL(clicked()), this, SLOT(slot_pushButton_ok()));
    //    double width = sceneRect().width();
    //    double height = sceneRect().height();
    //    double left = currentFrameList.at(0)->sceneBoundingRect().left()+width/2;
    //    double top = currentFrameList.at(0)->sceneBoundingRect().top()+height/2;
    //    double right = currentFrameList.at(0)->sceneBoundingRect().right()+width/2;
    //    double bottom = currentFrameList.at(0)->sceneBoundingRect().bottom()+height/2;
    //    optionDlg->ui.lineEdit_left->setText(QString::number(left));
    //    optionDlg->ui.lineEdit_top->setText(QString::number(top));
    //    optionDlg->ui.lineEdit_right->setText(QString::number(right));
    //    optionDlg->ui.lineEdit_bottom->setText(QString::number(bottom));

    //    optionDlg->exec();
}

void DropGraphicsScene::ModifyItem()
{
    //    optionDlg = new OptionDlg();
    //    connect(optionDlg->ui.pushButton_ok, SIGNAL(clicked()), this, SLOT(slot_pushButton_ok()));
    //    double width = sceneRect().width();
    //    double height = sceneRect().height();
    //    double left = currentFrameList.at(0)->sceneBoundingRect().left() + width / 2;
    //    double top = currentFrameList.at(0)->sceneBoundingRect().top() + height / 2;
    //    double right = currentFrameList.at(0)->sceneBoundingRect().right() + width / 2;
    //    double bottom = currentFrameList.at(0)->sceneBoundingRect().bottom() + height / 2;
    //    optionDlg->ui.lineEdit_left->setText(QString::number(left));
    //    optionDlg->ui.lineEdit_top->setText(QString::number(top));
    //    optionDlg->ui.lineEdit_right->setText(QString::number(right));
    //    optionDlg->ui.lineEdit_bottom->setText(QString::number(bottom));

    //    optionDlg->exec();
}

void DropGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "scenePos: " << event->scenePos() << ", pos: " << event->pos() << endl;
    event->accept();
}

void DropGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
    {
        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        Piece piece;
        dataStream >> piece.type >> piece.pixmap;
        QPointF point = event->scenePos();

        if(piece.type == "list")
        {
            Chip *chip = new Chip(QColor("steelBlue"), 100, 100);
            addItem(chip);
        }
        else if(piece.type == "tree")
        {

        }
        else if(piece.type == "table")
        {
            addTable(point);
        }
        else if(piece.type == "columnchart")
        {

        }
        else if(piece.type == "piechart")
        {

        }
        else if(piece.type == "tupu")
        {

        }



        event->setDropAction(Qt::MoveAction);
        event->accept();


    }
}

void DropGraphicsScene::addTable(const QPointF &point)
{
    /*
    QPen pen;
    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    QRadialGradient gradient(50, 50, 50, 50, 50);
    gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
    gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    QBrush brush(gradient);
    QGraphicsRectItem *item = addRect(point.x(), point.y(), width, height, pen, brush);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    */


    Frame *frame = new Frame(Rect1, myItemMenu);

    m_tableItems.append(frame);
    QGraphicsTextItem *text = new QGraphicsTextItem(tr("%1%2").arg(QStringLiteral("表格")).arg(m_tableItems.count()), frame);
    text->setDefaultTextColor(Qt::blue);
    text->setFont(QFont("微软雅黑", 24));
    text->setPos(point);
    addItem(frame);
    frame->setRect(point.x(), point.y(), 300, 200);
}

// 鼠标按下获取当前单选中的QGraphicsProxyWidget图元对象
void DropGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem *>itemList = items(event->scenePos());
        if(itemList.count() != 0)
        {
            //! [0]查找根Item即Frame
            QGraphicsItem *item;
            QGraphicsItem *baseItem = itemList.at(itemList.count() - 1);
            QGraphicsItem *parentItem = baseItem->parentItem();
            if (parentItem == nullptr)
            {
                item = baseItem;
            }
            else
            {
                item = parentItem;
            }
            //! [0]

            m_curFrame = qgraphicsitem_cast<Frame *>(item);
            m_curFrame->setOpacity(0.5);
            m_curFrame->setBrush(QColor("lightGreen"));
            m_curFrame->setPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

            //! 拖拽
            double mouseX = event->scenePos().x();
            double mouseY = event->scenePos().y();
            QRectF rect = m_curFrame->sceneBoundingRect();
            qDebug() << "mouse press, sceneBoundingRect-->" << rect;
            double myTop = rect.top();
            double myLeft = rect.left();
            double myBottom = rect.bottom();
            double myRight = rect.right();

            if ((myLeft - SMALL_INTERVAL < mouseX) && (mouseX < myLeft + SMALL_INTERVAL) && (myTop - SMALL_INTERVAL < mouseY) && (mouseY < myTop + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragLT;
            }
            else if ((myRight - SMALL_INTERVAL < mouseX) && (mouseX < myRight + SMALL_INTERVAL) && (myBottom - SMALL_INTERVAL < mouseY) && (mouseY < myBottom + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragRB;
            }
            else if ((myLeft - SMALL_INTERVAL < mouseX) && (mouseX < myLeft + SMALL_INTERVAL) && (myBottom - SMALL_INTERVAL < mouseY) && (mouseY < myBottom + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragLB;
            }
            else if ((myRight - SMALL_INTERVAL < mouseX) && (mouseX < myRight + SMALL_INTERVAL) && (myTop - SMALL_INTERVAL < mouseY) && (mouseY < myTop + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragRT;
            }
            else if ((myLeft - SMALL_INTERVAL < mouseX) && (mouseX < myLeft + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragL;
            }
            else if ((myRight - SMALL_INTERVAL < mouseX) && (mouseX < myRight + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragR;
            }
            else if ((myTop - SMALL_INTERVAL < mouseY) && (mouseY < myTop + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragT;
            }
            else if ((myBottom - SMALL_INTERVAL < mouseY) && (mouseY < myBottom + SMALL_INTERVAL))
            {
                is_drag = true;
                is_move = false;
                dragType = DragB;
            }
            else
            {
                is_drag = false;
                is_move = true;
//                m_startPos = m_curFrame->mapToScene(QPointF(0.0, 0.0));
                m_startPos = m_curFrame->boundingRect().topLeft();
                m_shiftOrg.setX(event->scenePos().x() - m_startPos.x());
                m_shiftOrg.setY(event->scenePos().y() - m_startPos.y());
                m_shiftOrg = event->scenePos();
            }

            m_curFrame->setDragType(dragType);
            qDebug() <<"select item, is_drag:" << is_drag << ", is_move:" << is_move;
        }
        else
        {
            if(m_curFrame)
            {
                m_curFrame->setBrush(QColor("transparent"));
                m_curFrame->setPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                m_curFrame->setOpacity(1);
                qDebug() << "no item select...";
            }
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

// 鼠标移动过程中跟随位置改变
void DropGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(is_move)
    {
        qreal x_offset = event->scenePos().x() - m_shiftOrg.x();
        qreal y_offset = event->scenePos().y() - m_shiftOrg.y();
        qreal width = m_curFrame->rect().width();
        qreal height = m_curFrame->rect().height();
        qDebug() << x_offset << "," << y_offset << "," << width << "," << height << "," << m_startPos << endl;

        m_curFrame->setRect(m_startPos.x() + x_offset, m_startPos.y() + y_offset, width, height);
        m_curFrame->resetChildrenPos();
    }

    if(!is_drag)
    {
        QList<QGraphicsItem *>itemList = items(event->scenePos(), Qt::IntersectsItemShape);
        if(itemList.count() != 0)
        {
            //! [0]查找根Item即Frame
            QGraphicsItem *item;
            QGraphicsItem *baseItem = itemList.at(itemList.count() - 1);
            QGraphicsItem *parentItem = baseItem->parentItem();
            if (parentItem == nullptr)
            {
                item = baseItem;
            }
            else
            {
                item = parentItem;
            }
            //! [0]
            m_curFrame = qgraphicsitem_cast<Frame *>(item);

            QRectF rect = m_curFrame->sceneBoundingRect();
            double mouseX = event->scenePos().x();
            double mouseY = event->scenePos().y();
            //qDebug() << "mouse move, sceneBoundingRect-->" << rect;
            double myTop = rect.top();
            double myLeft = rect.left();
            double myBottom = rect.bottom();
            double myRight = rect.right();

            //改变鼠标形状
            if (((myLeft - SMALL_INTERVAL < mouseX) && (mouseX < myLeft + SMALL_INTERVAL) && (myTop - SMALL_INTERVAL < mouseY) && (mouseY < myTop + SMALL_INTERVAL)) || ((myRight - SMALL_INTERVAL < mouseX) && (mouseX < myRight + SMALL_INTERVAL) && (myBottom - SMALL_INTERVAL < mouseY) && (mouseY < myBottom + SMALL_INTERVAL)))
            {
                m_curFrame->setCursor(Qt::SizeFDiagCursor);
            }
            else if (((myLeft - SMALL_INTERVAL < mouseX) && (mouseX < myLeft + SMALL_INTERVAL) && (myBottom - SMALL_INTERVAL < mouseY) && (mouseY < myBottom + SMALL_INTERVAL)) || ((myRight - SMALL_INTERVAL < mouseX) && (mouseX < myRight + SMALL_INTERVAL) && (myTop - SMALL_INTERVAL < mouseY) && (mouseY < myTop + SMALL_INTERVAL)))
            {
                m_curFrame->setCursor(Qt::SizeBDiagCursor);
            }
            else if (((myLeft - SMALL_INTERVAL < mouseX) && (mouseX < myLeft + SMALL_INTERVAL)) || ((myRight - SMALL_INTERVAL < mouseX) && (mouseX < myRight + SMALL_INTERVAL)))
            {
                m_curFrame->setCursor(Qt::SizeHorCursor);
            }
            else if (((myTop - SMALL_INTERVAL < mouseY) && (mouseY < myTop + SMALL_INTERVAL)) || ((myBottom - SMALL_INTERVAL < mouseY) && (mouseY < myBottom + SMALL_INTERVAL)))
            {
                m_curFrame->setCursor(Qt::SizeVerCursor);
            }
            else
            {
                m_curFrame->setCursor(Qt::ArrowCursor);
            }
        }
    }
    else
    {
        //! 拖动改变Item大小
        m_curFrame->drawing(event);
        update();
    }

    emit pos(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}
// 鼠标释放后作为最后的位置
void DropGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(is_move)
    {
//        QPointF newPos(event->scenePos().x() - m_shiftOrg.x(), event->scenePos().y() - m_shiftOrg.y());
//        m_curFrame->setPos(newPos);
//        QRectF re = m_curFrame->rect();
//        qDebug() << "scene bounding rect-->" << m_curFrame->sceneBoundingRect() << ", pos:" << newPos << ", curFrame.rect:" << re << endl;
    }
    is_drag = false;
    is_move = false;
    QGraphicsScene::mouseReleaseEvent(event);
}
