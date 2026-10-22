#include "vehicle.hpp"
#include "rental_contract.hpp"
#include <iostream>
#include <memory>

int main()
{
    std::cout << "STARTING VEHICLE RENTAL SYSTEM TESTS (SMART POINTERS)\n\n";

    std::cout << "1: unique_ptr and ownership transfer\n";
    {
        // Создание автомобиля через std::make_unique (единственный владелец)
        std::unique_ptr<rental::Vehicle> uniqueCar = std::make_unique<rental::Vehicle>(101, "Tesla Model 3", 85.0, 15000.0);
        uniqueCar->AddMaintenanceRecord(1, "Battery check and tire replacement", 250.0, 1728000000);

        // Передаем владение с помощью std::move в другой unique_ptr
        std::unique_ptr<rental::Vehicle> newOwnerCar = std::move(uniqueCar);

        if (!uniqueCar) {
            std::cout << "[info] uniqueCar is now empty after std::move\n";
        }
        std::cout << "[info] New owner is managing the car: " << newOwnerCar->GetModel() << "\n\n";
    } // Здесь uniqueCar уничтожается вместе со своей историей техобслуживания (композиция).

    std::cout << "2: shared_ptr and owner counter (use_count)\n";
    {
        // Создаем автомобиль через std::make_shared
        std::shared_ptr<rental::Vehicle> sharedCar = std::make_shared<rental::Vehicle>(102, "Nissan Leaf", 90.0, 5000.0);
        std::cout << "Owner count (use_count): " << sharedCar.use_count() << "\n";

        {
            // Появляется второй владелец (копирование shared_ptr)
            std::shared_ptr<rental::Vehicle> anotherOwner = sharedCar;
            std::cout << "Owner count after copying: " << sharedCar.use_count() << "\n";
        } // anotherOwner уничтожается здесь

        std::cout << "Owner count after leaving the block: " << sharedCar.use_count() << "\n\n";
    } // sharedCar уничтожается здесь, так как счетчик дошел до 0.

    std::cout << "3: weak_ptr and aggregation in RentalContract\n";
    {
        // Создаем автомобиль через shared_ptr, чтобы договоры могли наблюдать за ним через weak_ptr
        std::shared_ptr<rental::Vehicle> rentalCar = std::make_shared<rental::Vehicle>(103, "Audi e-tron", 75.0, 12000.0);

        {
            // Создаем контракт, передавая shared_ptr
            rental::RentalContract contract(501, "Alex", 5, rentalCar, 3, 50.0);

            if (contract.ProcessIssue()) {
                std::cout << "Contract successfully issued! Car is in use.\n";
            }
        } // Договор уничтожается, но автомобиль жив, так как на него все еще ссылается rentalCar

        std::cout << "Resetting the last shared_ptr owner...\n";
        rentalCar.reset(); // Автомобиль уничтожается

        std::cout << "Test completed. No delete operators were used in the program!\n";
    }

    std::cout << "\nTESTING COMPLETED, EXITING MAIN\n";
    return 0;
}