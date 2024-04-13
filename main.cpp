#include <iostream>
#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/magnet_uri.hpp>

/*
    Features:
    - magnet link and media type as input
    - downloads the torrent file
    - once completed, moves the file to the desired location
*/

int validate_input(int argc, char const* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <magnet_link> <media_type (movies|tv-shows)>" << std::endl;
        return 1;
    }

    std::string media_type = argv[2];
    if (media_type != "movies" && media_type != "tv-shows") {
        std::cerr << "Invalid media type. Please use either 'movies' or 'tv-shows'." << std::endl;
        return 2;
    }

    return 0;
}

lt::add_torrent_params create_torrent_params(std::string magnet_link, std::string path)
{
    lt::add_torrent_params params = lt::parse_magnet_uri(magnet_link);
    params.save_path = path;

    return params;
}

int main(int argc, char const* argv[])
{
    int validation = validate_input(argc, argv);
    if (validation != 0) return validation;

    std::string magnet_link = argv[1];
    std::string media_type = argv[2];
    std::string path = "/mnt/external-hdd/" + media_type + "/";

    lt::add_torrent_params params = create_torrent_params(magnet_link, path);
    
    return 0;
}