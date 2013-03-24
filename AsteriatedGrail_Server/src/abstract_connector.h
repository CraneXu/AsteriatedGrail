#ifndef ASTERIATEDGRAIL_SRC_ABSTRACT_CONNECTOR_H
#define ASTERIATEDGRAIL_SRC_ABSTRACT_CONNECTOR_H

#include <QObject>

class AbstractConnector : public QObject
{
    Q_OBJECT
public:
    explicit AbstractConnector();
    virtual QString token();
signals:
    
public slots:
    
};

#endif // ASTERIATEDGRAIL_SRC_ABSTRACT_CONNECTOR_H
