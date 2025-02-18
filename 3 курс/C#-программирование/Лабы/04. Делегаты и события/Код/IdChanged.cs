public sealed class IdChanged : EventArgs
{
    public int OldId { get; }
    public int NewId { get; }

    public IdChanged(int oldId, int newId)
    {
        OldId = oldId;
        NewId = newId;
    }
}