#include "vehicle.hpp"
#include <iostream>
#include <utility>
#include <memory>

namespace rental
{
    // Основной конструктор
    Vehicle::Vehicle(std::uint64_t id, std::string_view model, double batteryLevel, double mileage)
        : m_id(id),
        m_model(model),
        m_batteryLevel(batteryLevel),
        m_mileage(mileage),
        m_maintenanceCount(0) // Инициализируем только текущий счетчик записей
    {
        std::cout << "[" << TAG << "] Created vehicle id: " << m_id << ", model: " << m_model << "\n";
    }

    // Метод добавления записи о техобслуживании
    void Vehicle::AddMaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp)
    {
        if (m_maintenanceCount < 10)
        {
            // Создаем одиночный unique_ptr и помещаем в наш фиксированный массив
            m_maintenanceHistory[m_maintenanceCount] = std::make_unique<MaintenanceRecord>(id, description, cost, timestamp);
            m_maintenanceCount++;
            std::cout << "[" << TAG << "] Added maintenance record to vehicle id: " << m_id << "\n";
        }
    }

    // Проверка возможности аренды (заряд >= 20%)
    bool Vehicle::CanBeRented() const
    {
        return m_batteryLevel >= 20.0;
    }

} // namespace rental