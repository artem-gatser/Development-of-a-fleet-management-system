using System;

namespace FleetManagement
{
    class Program
    {

        // Создает временный объект книги внутри метода и возвращает слабую ссылку на него.
        static WeakReference CreateTemporaryBookWatcher()
        {
            var tempBook = new BookForGc("Списанная книга", 1);
            return new WeakReference(tempBook);
        }

        static void Main(string[] args)
        {
            // Поддержка кириллицы в консоли
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            Console.WriteLine("СТАРТ ТЕСТИРОВАНИЯ\n");

            // Создание автомобиля и композиция
            var myCar = new Vehicle(101, "Tesla Model 3", 85.0, 15000.0);
            myCar.AddMaintenanceRecord(1, "Проверка батареи", 250.0, 1728000000);

            // Тест 1: Неуспешная аренда (маленький стаж)
            Console.WriteLine("\nТЕСТ 1: Попытка аренды клиентом со стажем 1 год");
            var badContract = new RentalContract(501, "Иван", 1, myCar, 3, 50.0);
            badContract.ProcessIssue();

            // Тест 2: Успешная аренда
            Console.WriteLine("\nТЕСТ 2: Успешная аренда клиентом со стажем 5 лет");
            var goodContract = new RentalContract(502, "Алексей", 5, myCar, 5, 50.0);
            if (goodContract.ProcessIssue())
            {
                goodContract.CompleteContract();
            }

            // Демонстрация памяти: Ссылки и копии
            Console.WriteLine("\nДЕМОНСТРАЦИЯ ПАМЯТИ: Ссылки и копии");
            var firstVehicle = new Vehicle(102, "Nissan Leaf", 90.0, 5000.0);
            var secondVehicle = firstVehicle;
            Console.WriteLine($"firstVehicle == secondVehicle: {firstVehicle == secondVehicle}");

            // Сравнение со struct (передача по значению)
            var moneyA = new Money { Rubles = 150, Kopecks = 50 };
            var moneyB = moneyA;
            moneyB.Rubles = 300;
            Console.WriteLine($"Структура struct Money A (исходная): {moneyA.Rubles} руб. (не изменилась)");

            // Демонстрация освобождения ресурса через IDisposable и using
            Console.WriteLine("\nДЕМОНСТРАЦИЯ: Освобождение ресурса (using)");
            using (var log = new IssueLog("Абонемент проката"))
            {
                log.Write("выдан автомобиль Tesla Model 3");
            }

            // Демонстрация сборщика мусора через WeakReference
            Console.WriteLine("\nДЕМОНСТРАЦИЯ: Сборщик мусора (Garbage Collector)");
            var watcher = CreateTemporaryBookWatcher();
            Console.WriteLine($"Объект жив до сборки мусора? {watcher.IsAlive}");

            GC.Collect(); // Принудительный сбор мусора
            GC.WaitForPendingFinalizers(); // Ожидание завершения очистки
            Console.WriteLine($"Объект жив после GC.Collect()? {watcher.IsAlive}");

            Console.WriteLine("\nТЕСТИРОВАНИЕ ЗАВЕРШЕНО");
        }
    }

    public struct Money
    {
        public int Rubles;
        public int Kopecks;
    }

    public class BookForGc
    {
        public string Title { get; }
        public int Copies { get; }
        public BookForGc(string title, int copies) => (Title, Copies) = (title, copies);
    }
}