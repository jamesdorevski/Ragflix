#include <iostream>
#include <libtorrent/session.hpp>

/*
    Features:
    - magnet link and media type as input
    - downloads the torrent file
    - once completed, moves the file to the desired location
*/

int validate_input(int argc, char const* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <magnet_link> <media_type (movie|tv)>" << std::endl;
        return 1;
    }

    std::string media_type = argv[2];
    if (media_type != "movie" && media_type != "tv") {
        std::cerr << "Invalid media type. Please use either 'movie' or 'tv'." << std::endl;
        return 2;
    }

    return 0;
}

int main(int argc, char const* argv[])
{
    int validation = validate_input(argc, argv);
    if (validation != 0) return validation;

    return 0;
}