#ifndef ASTERIATEDGRAIL_SRC_ABSTRACT_CONNECTOR_H
#define ASTERIATEDGRAIL_SRC_ABSTRACT_CONNECTOR_H

#include <QObject>

class AbstractConnector : public QObject
{
    Q_OBJECT
public:
    explicit AbstractConnector();
    virtual ~AbstractConnector();
    virtual QString token() const = 0;
signals:
    
public slots:
    
};

#endif // ASTERIATEDGRAIL_SRC_ABSTRACT_CONNECTOR_H
