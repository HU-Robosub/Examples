namespace WebApplication1;

using System;
using System.IO;

public class FileAppenderWatcher : FileSystemWatcher
{
    public event EventHandler<FileAppendedEventArgs> FileAppended;

    public FileAppenderWatcher(string directory, string filter) : base(directory, filter)
    {
        // Set up the FileSystemWatcher properties
        NotifyFilter = NotifyFilters.LastWrite;
        IncludeSubdirectories = false;

        // Subscribe to the Changed event
        Changed += OnFileChanged;
    }

    private void OnFileChanged(object sender, FileSystemEventArgs e)
    {
        if (e.ChangeType == WatcherChangeTypes.Changed)
        {
            // Raise the FileAppended event with file path and change type
            FileAppended?.Invoke(this, new FileAppendedEventArgs(e.FullPath, e.ChangeType));
        }
    }
}

public class FileAppendedEventArgs : EventArgs
{
    public string FilePath { get; }
    public WatcherChangeTypes ChangeType { get; }

    public FileAppendedEventArgs(string filePath, WatcherChangeTypes changeType)
    {
        FilePath = filePath;
        ChangeType = changeType;
    }
}
