// Статический класс для методов расширения
using Showcase;
using DataDevice;
using System;

public static class ShowcaseExtensions
{

    // Подписка на событие изменения идентификатора витрины
    public static void UpdateBarcode<T>(this T device, IShowcase<T> showcase) where T : class, IDataDevice
    {
        device.UpdateBarcode(showcase, showcase.FindById(device.Id));
    }

    // Подписка на событие с учётом позиции устройства
    public static void UpdateBarcode<T>(this T device, IShowcase<T> showcase, int index) where T : class, IDataDevice
    {
        if (device != null)
        {
            device.Barcode.Text = $"{device.Id} {showcase.Id} {index}";
        }
    }
}
