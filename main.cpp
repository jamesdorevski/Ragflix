#include <iostream>
#include <chrono>
#include <thread>

#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/session_params.hpp>

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

lt::settings_pack create_settings_pack()
{
    lt::settings_pack p;
    p.set_int(lt::settings_pack::alert_mask, lt::alert_category::status | lt::alert_category::error);

    return p;
}

int halt_until_download_complete(lt::session& session)
{
    bool downloading = true;

    while (downloading) {
        std::vector<lt::alert*> alerts;
        session.pop_alerts(&alerts);

        for (lt::alert* alert : alerts) {
            if (lt::alert_cast<lt::torrent_finished_alert>(alert)) {
                downloading = false;
                break;
            }

            if (lt::alert_cast<lt::torrent_error_alert>(alert)) {
                std::cerr << "Error downloading torrent. Aborting..." << std::endl;
                return 3;
            }

            if (auto update_alert = lt::alert_cast<lt::state_update_alert>(alert)) {
                for (auto& status : update_alert->status) {
                    float download_rate_mbps = status.download_payload_rate / 125000.0f;
                    std::cout << "Download progress: " << status.progress * 100 << "%" << " @ " << download_rate_mbps << " Mbps" << std::endl;

                    if (status.download_payload_rate > 0) {
                        int remaining_bytes = status.total_wanted - status.total_wanted_done;
                        int remaining_seconds = remaining_bytes / status.download_payload_rate;

                        std::cout << "Estimated time remaining: " << remaining_seconds << " seconds" << std::endl;
                    }
                }
            }
        }

        session.post_torrent_updates();

        std::this_thread::sleep_for(std::chrono::seconds(5));   
    }

    return 0;
}

int main(int argc, char const* argv[])
{
    int validation = validate_input(argc, argv);
    if (validation != 0) return validation;

    std::string magnet_link = argv[1];
    std::string media_type = argv[2];
    // std::string path = "/mnt/external-hdd/" + media_type + "/";
    std::string path = "/home/james/" + media_type + "/";

    lt::add_torrent_params params = create_torrent_params(magnet_link, path);
    lt::settings_pack settings = create_settings_pack();
    lt::session session(settings);
    
    std::cout << "Downloading torrent " << params.name << " to " << path << "..." << std::endl;

    lt::torrent_handle handle = session.add_torrent(std::move(params));

    int download_status = halt_until_download_complete(session);
    if (download_status != 0) return download_status;

    return 0;
}