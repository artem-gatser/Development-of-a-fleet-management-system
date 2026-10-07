#include "maintenance_record.hpp"
#include <iostream>

namespace rental
{

    MaintenanceRecord::MaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp)
        : m_id{ id }
        , m_workDescription{ description }
        , m_cost{ cost }
        , m_dateTimestamp{ timestamp }
    {
        std::cout << "[" << TAG << "] Created maintenance record id: " << m_id
            << ", cost: " << m_cost << "\n";
    }

    MaintenanceRecord::~MaintenanceRecord()
    {
        std::cout << "[" << TAG << "] Destroyed maintenance record id: " << m_id << "\n";
    }

} // namespace rental