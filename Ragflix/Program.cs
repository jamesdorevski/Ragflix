// add magnet link using add command 
// enum - movie or tv show 
// pass it to torrent client 
// download it 
// once done, move to the correct folder 

using System.CommandLine;
using Ragflix.Add;

internal class Program
{
    private static async Task<int> Main(string[] args)
    {
        var addCommand = Cli.AddCommand();

        var rootCommand = new RootCommand("Add movies and tv shows to the Jellyfin library.");
        rootCommand.AddCommand(addCommand);

        return await rootCommand.InvokeAsync(args);
    }
}