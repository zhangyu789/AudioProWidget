// Device.h
#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include <QList>

// Device 类声明
class Device
{
public:
    // 构造函数
    Device(const QString& name, const QString& type, const QList<QString>& subclasses);

    // 获取设备名称
    QString getName() const;

    // 获取设备类型
    QString getType() const;

    // 获取子类列表
    QList<QString> getSubclasses() const;

    // 设置设备名称
    void setName(const QString& name);

    // 设置设备类型
    void setType(const QString& type);

    // 设置子类列表
    void setSubclasses(const QList<QString>& subclasses);

private:
    QString m_name;             // 设备名称
    QString m_type;             // 设备类型
    QList<QString> m_subclasses; // 子类列表
};

#endif // DEVICE_H
