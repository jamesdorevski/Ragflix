namespace Ragflix.Add;

internal static class Handlers 
{
    public static async Task<int> DownloadAsync(AddCommand command)
    {
        string saveDirectory = command.TorrentType switch 
        {
            1 => "/mnt/external-hdd/movies",
            2 => "/mnt/external-hdd/tv-shows",
            _ => throw new ArgumentException("Invalid torrent type.")
        };

        var client = new TorrentClient();
        await client.DownloadMagnetLinkAsync(command.MagnetLink, saveDirectory);

        return 0;
    }
}