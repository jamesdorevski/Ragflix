
using MonoTorrent;
using MonoTorrent.Client;

internal class TorrentClient
{
    public async Task DownloadMagnetLinkAsync(string magnetLink, string saveDirectory)
    {
        if (!MagnetLink.TryParse(magnetLink, out MagnetLink link))
            throw new ArgumentException("Invalid magnet link.");

        using var engine = new ClientEngine();
        var torrent = await engine.AddAsync(link, saveDirectory);

        await torrent.StartAsync();
        while (!torrent.Complete)
        {
            Console.Clear();
            Console.WriteLine($"Progress: {torrent.Progress:0.00}%");
            Console.WriteLine($"Download speed: {torrent.Monitor.DownloadSpeed / 1024:0.00} KB/s");
            Console.WriteLine($"Upload speed: {torrent.Monitor.UploadSpeed / 1024:0.00} KB/s");
            Console.WriteLine($"Bytes downloaded: {torrent.Monitor.DataBytesDownloaded / 1024 / 1024:0.00} MB");
            Console.WriteLine($"Total size: {torrent.Size / 1024 / 1024:0.00} MB");
            Console.WriteLine($"Download location: {saveDirectory}");
            await Task.Delay(5000);
        }

        await torrent.StopAsync();

        Console.WriteLine("Download complete.");
    }
}