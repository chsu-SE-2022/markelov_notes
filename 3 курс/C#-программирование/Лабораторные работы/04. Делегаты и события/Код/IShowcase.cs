using DataDevice;

namespace Showcase

{
    // Интерфейс IShowcase, определяющий основные методы и свойства
    public interface IShowcase<T> where T : class, IDataDevice
    {
        int Id { get; set; }
        T this[int index] { get; set; }
        void AddDevice(T device);
        void AddDevice(T device, int index);
        void RemoveDevice();
        void RemoveDevice(int index);
        void ReplaceDevice(int index, T newDevice);
        void SwapDevices(int index1, int index2);
        int FindById(int deviceId);
        int FindByName(string name);
        void SortById();
        void SortByName();
        void MoveDevice<TT>(T device, IShowcase<TT> targetShowcase) where TT : class, IDataDevice;
    }
}