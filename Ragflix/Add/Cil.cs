using System.CommandLine;

namespace Ragflix.Add;

internal static class Cli
{
    public static Command AddCommand()
    {
        var magnetLink = new Option<string>("-m", description: "Torrent magnet link to add.")
        {
            IsRequired = true
        };

        var torrentType = new Option<int>(
            "-t",
            description: "Torrent type to add. 1 for movie, 2 for tv series.",
            parseArgument: result =>
            {
                int input = int.Parse(result.Tokens[0].Value);
                if (input != 1 && input != 2)
                    throw new ArgumentException("Invalid torrent type.");

                return input;
            }
        )
        {
            IsRequired = true
        };
        
        var addCommand = new Command("add", "Add a torrent to the library.")
        {
            magnetLink,
            torrentType
        };

        // add handler

        return addCommand;
    }
}
