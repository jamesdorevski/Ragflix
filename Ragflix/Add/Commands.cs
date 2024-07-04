namespace Ragflix.Add;

internal record AddCommand(
    string MagnetLink,
    int TorrentType
);