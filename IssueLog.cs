using System;

namespace FleetManagement
{
    // Класс журнала для демонстрации безопасного управления ресурсами с помощью интерфейса IDisposable и блока using.
    public sealed class IssueLog : IDisposable
    {
        // Название или назначение данного журнала
        private readonly string _title;

        // Конструктор: вызывается при создании журнала. 
        public IssueLog(string title)
        {
            _title = title;
            Console.WriteLine($"[+] журнал открыт: {_title}");
        }

        // Записывает строку в журнал с небольшим отступом.
        public void Write(string line) => Console.WriteLine($"    {line}");

        // Вызывается автоматически при выходе из блока using для освобождения ресурсов.
        public void Dispose() => Console.WriteLine($"[-] журнал закрыт: {_title}");
    }
}