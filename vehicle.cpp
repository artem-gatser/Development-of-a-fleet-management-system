#include "vehicle.hpp"
#include <iostream>
#include <utility>

namespace rental
{
    // Основной конструктор
    Vehicle::Vehicle(std::uint64_t id, std::string_view model, double batteryLevel, double mileage)
        : m_id(id),
        m_model(model),
        m_batteryLevel(batteryLevel),
        m_mileage(mileage),
        m_maintenanceHistory(new MaintenanceRecord* [10]), // Выделяем массив на 10 указателей
        m_maintenanceCapacity(10),
        m_maintenanceCount(0)
    {
        // Зануляем все указатели в массиве
        for (std::size_t i = 0; i < m_maintenanceCapacity; ++i) {
            m_maintenanceHistory[i] = nullptr;
        }
        std::cout << "[" << TAG << "] Created vehicle id: " << m_id << ", model: " << m_model << "\n";
    }

    // Деструктор (очистка каждого динамического объекта и самого массива)
    Vehicle::~Vehicle()
    {
        std::cout << "[" << TAG << "] Destroyed vehicle id: " << m_id << ". Cleaning maintenance history...\n";
        if (m_maintenanceHistory)
        {
            for (std::size_t i = 0; i < m_maintenanceCount; ++i)
            {
                delete m_maintenanceHistory[i]; // Удаляем каждую запись о техобслуживании
            }
            delete[] m_maintenanceHistory;      // Удаляем сам массив указателей
        }
    }

    // Move-конструктор
    Vehicle::Vehicle(Vehicle&& other) noexcept
        : m_id(other.m_id),
        m_model(std::move(other.m_model)),
        m_batteryLevel(other.m_batteryLevel),
        m_mileage(other.m_mileage),
        m_maintenanceHistory(other.m_maintenanceHistory),
        m_maintenanceCapacity(other.m_maintenanceCapacity),
        m_maintenanceCount(other.m_maintenanceCount)
    {
        other.m_maintenanceHistory = nullptr;
        other.m_maintenanceCapacity = 0;
        other.m_maintenanceCount = 0;
    }

    // Move-оператор присваивания
    Vehicle& Vehicle::operator=(Vehicle&& other) noexcept
    {
        if (this != &other)
        {
            // Удаляем свою старую память перед принятием новой
            if (m_maintenanceHistory)
            {
                for (std::size_t i = 0; i < m_maintenanceCount; ++i)
                {
                    delete m_maintenanceHistory[i];
                }
                delete[] m_maintenanceHistory;
            }

            m_id = other.m_id;
            m_model = std::move(other.m_model);
            m_batteryLevel = other.m_batteryLevel;
            m_mileage = other.m_mileage;
            m_maintenanceHistory = other.m_maintenanceHistory;
            m_maintenanceCapacity = other.m_maintenanceCapacity;
            m_maintenanceCount = other.m_maintenanceCount;

            other.m_maintenanceHistory = nullptr;
            other.m_maintenanceCapacity = 0;
            other.m_maintenanceCount = 0;
        }
        return *this;
    }

    // Метод добавления записи о техобслуживании
    void Vehicle::AddMaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp)
    {
        if (m_maintenanceCount < m_maintenanceCapacity)
        {
            m_maintenanceHistory[m_maintenanceCount] = new MaintenanceRecord(id, description, cost, timestamp);
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