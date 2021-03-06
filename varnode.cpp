#include "varnode.h"
#include "diagramwindow.h"
#include "colordlg.h"

VarNode::VarNode()
{
    box=new QComboBox;
    num=0;
    for(int i=0;i<6;i++)
    {
        flags[i]=false;
        array[i]=new VardefNode;
        array[i]->setFlag(ItemIsMovable,false);
    }

    identifier="VarNode";
}

VarNode::~VarNode()
{
    for(int i=0;i<6;i++)
        delete array[i];
}

QPolygonF VarNode::outlineRect() const
{
    QPolygonF poly;
    poly<<QPointF(10,16)<<QPointF(20,0)<<QPointF(10,-16)
       <<QPointF(-10,-16)<<QPointF(-20,0)<<QPointF(-10,16);
    return poly;
}

QRectF VarNode::boundingRect() const
{
    return QRectF(-20,-20,40,40);
}

QPainterPath VarNode::shape()  const
{
    QPolygonF poly=outlineRect();
    QPainterPath path;
    path.addPolygon(poly);
    return path;
}

void VarNode::paint(QPainter *painter,
                    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(outlineColor());
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(backgroundColor());

    QPolygonF poly = outlineRect();
    painter->drawPolygon(poly);
    QRectF rect=boundingRect();

    painter->setPen(textColor());
    painter->drawText(rect, Qt::AlignCenter, text());
}

QVariant VarNode::itemChange(GraphicsItemChange change,
                    const QVariant &value)
{
    if (change & ItemPositionHasChanged) {
        int a=0;
        for(;a<6;a++)
        {
            if(flags[a])
            {
                int i=a%3;
                int j;
                if(a==0||a==2)j=-17;
                else if(a==3||a==5)j=17;
                else if(a==1)j=-35;
                else j=35;
                array[a]->setPos(pos().x() + (1-i)*30,
                                 pos().y() + j);
            }
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
