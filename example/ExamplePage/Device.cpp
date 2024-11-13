// Device.cpp
#include "Device.h"

// 构造函数实现
Device::Device(const QString& name, const QString& type, const QList<QString>& subclasses)
    : m_name(name), m_type(type), m_subclasses(subclasses)
{
}

// 获取设备名称
QString Device::getName() const
{
    return m_name;
}

// 获取设备类型
QString Device::getType() const
{
    return m_type;
}

// 获取子类列表
QList<QString> Device::getSubclasses() const
{
    return m_subclasses;
}

// 设置设备名称
void Device::setName(const QString& name)
{
    m_name = name;
}

// 设置设备类型
void Device::setType(const QString& type)
{
    m_type = type;
}

// 设置子类列表
void Device::setSubclasses(const QList<QString>& subclasses)
{
    m_subclasses = subclasses;
}
