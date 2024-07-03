# Ragflix

Download and store media directly on our Plex server.

## Usage

```shell
Usage: ./Ragflix <magnet_link> <media_type (movies|tv-shows)>

Arguments:
- magnet_link: Magnet link for the torrent you wish to download
- media_type: Used to store media in appropriate directory for Plex's library scan feature. Options are: (movies|tv-shows)
```

### Sending commands remotely via ssh

A succinct way of using Ragflix is by sending a remote execution command via ssh. Here's an example usage whilst connected to our home network: 

```shell
ssh pi@raspberrypi '/home/pi/src/ragflix'
```