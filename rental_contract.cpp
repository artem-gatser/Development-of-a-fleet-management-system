#include "rental_contract.hpp"
#include <iostream>

namespace rental
{

    // Конструктор договора аренды (принимает shared_ptr, сохраняет как weak_ptr)
    RentalContract::RentalContract(std::uint64_t id, std::string_view clientName, std::uint32_t driverExperience,
        std::shared_ptr<Vehicle> vehicle, std::uint32_t days, double dailyRate)
        : m_contractId{ id }
        , m_clientName{ clientName }
        , m_driverExperienceYears{ driverExperience }
        , m_rentalDays{ days }
        , m_dailyRate{ dailyRate }
        , m_totalCost{ days * dailyRate }
        , m_targetVehicle{ vehicle } // неявное преобразование shared_ptr в weak_ptr (агрегация)
    {
        std::cout << "[" << TAG << "] Created contract id: " << m_contractId
            << " for client: " << m_clientName << "\n";
    }

    // Деструктор договора
    RentalContract::~RentalContract()
    {
        std::cout << "[" << TAG << "] Destroyed contract id: " << m_contractId
            << ". The car itself remains safe and sound (aggregation).\n";
    }

    // Оформление договора с проверками правил через .lock() для weak_ptr
    bool RentalContract::ProcessIssue()
    {
        // Превращаем weak_ptr в temporary shared_ptr для проверки, жив ли объект
        auto lockedVehicle = m_targetVehicle.lock();
        if (!lockedVehicle)
        {
            std::cout << "[" << TAG << "] Error: Vehicle no longer exists for contract id: " << m_contractId << "\n";
            return false;
        }

        // Проверка водительского стажа (минимум 3 года)
        if (m_driverExperienceYears < 3)
        {
            std::cout << "[" << TAG << "] Rental denied for contract id: " << m_contractId
                << " (driver experience is " << m_driverExperienceYears
                << " years, minimum required is 3 years)\n";
            return false;
        }

        // Проверка заряда батареи автомобиля через заблокированный указатель
        if (!lockedVehicle->CanBeRented())
        {
            std::cout << "[" << TAG << "] Rental denied: Vehicle cannot be rented due to technical constraints.\n";
            return false;
        }

        m_state = ContractState::eActive;
        std::cout << "[" << TAG << "] Contract id: " << m_contractId << " successfully issued and active!\n";
        return true;
    }

    // Завершение договора
    void RentalContract::CompleteContract()
    {
        m_state = ContractState::eCompleted;
        std::cout << "[" << TAG << "] Contract id: " << m_contractId << " is now completed.\n";
    }

} // namespace rental