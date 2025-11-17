#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// ---------------------------------------------------------------
// StoryNode: Represents one moment in the story.
// Each node contains:
//
// - text: The story narration shown to the player.
// - options: Player choices at this story point.
// - nextNodes: Indexes pointing to the next StoryNode in the story tree.
//
// Note: If options.size() == 0, it is an ENDING node.
// ---------------------------------------------------------------
struct StoryNode {
    string text;
    vector<string> options;
    vector<int> nextNodes;
};

// Typewriter printing for atmosphere
void slowPrint(const string& text, int delay = 10) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << "\n";
}

// Displays a block of text with spacing
void blockText(const string& text) {
    cout << "\n";
    slowPrint(text);
    cout << "\n";
}

// Gets user choice safely
int getChoice(int maxOption) {
    int c;
    while (true) {
        cout << "Choose (1-" << maxOption << "): ";
        cin >> c;
        if (cin.good() && c >= 1 && c <= maxOption) return c - 1;

        // Clean invalid input
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice. Try again.\n";
    }
}

int main() {
    // ---------------------------------------------------------------
    // STORY STRUCTURE:
    //
    // We store all story points (nodes) in a vector<StoryNode>.
    // Every node's nextNodes vector holds INDEXES of other nodes.
    //
    // This creates a branching **story tree**, allowing multiple paths.
    // ---------------------------------------------------------------

    vector<StoryNode> story;

    // 0: Opening scene
    story.push_back({
        "You awaken at dusk, standing on the broken road leading into the abandoned city of Asterfall.\n"
        "A cold wind moves through shattered towers. Behind you is the forest. Ahead, the ruins.\n"
        "A faint light glows from a library to your left, while a distant metallic ringing comes from the right.",
        {"Enter the glowing library", "Follow the metallic ringing", "Head deeper into the city center"},
        {1, 2, 3}
        });

    // 1: Library
    story.push_back({
        "Inside the library, shelves lean like tired giants. A lantern flickers.\n"
        "On a desk sits an old journal with a metal clasp. Footsteps echo upstairs.",
        {"Inspect the journal", "Climb the stairs"},
        {4, 5}
        });

    // 2: Metallic ringing
    story.push_back({
        "You follow the ringing to a workshop. Tools are scattered everywhere.\n"
        "A cracked automaton lies on a table, its gears grinding weakly.",
        {"Try to repair the automaton", "Search the workshop"},
        {6, 7}
        });

    // 3: City center
    story.push_back({
        "You step into the city plaza. Empty market stalls line the streets.\n"
        "A huge statue of an ancient king stands in the center, its eyes glowing faintly.",
        {"Inspect the statue", "Take shelter inside a nearby tavern"},
        {8, 9}
        });

    // 4: Inspect journal — ending
    story.push_back({
        "You open the journal. Its pages tell the truth of Asterfall: the city was frozen in time\n"
        "by its own scholars to escape a coming disaster.\n\n"
        "As you finish reading, the lantern brightens.\n"
        "The room dissolves into golden dust.\n\n"
        "✨ Ending: Keeper of Forgotten Knowledge ✨",
        {}, {}
        });

    // 5: Upstairs in library
    story.push_back({
        "You climb the stairs. A hooded figure stands in front of a tall window.\n"
        "\"You came back,\" they whisper.\n"
        "Their hand extends, offering you a silver key.",
        {"Take the key", "Refuse and demand answers"},
        {10, 11}
        });

    // 6: Repair automaton — ending
    story.push_back({
        "You tighten gears and reconnect wires. The automaton's eyes flicker to life.\n"
        "\"Thank… you…\" it says before collapsing again.\n"
        "A secret panel opens, revealing a hidden path out of the city.\n\n"
        "✨ Ending: The Gentle Mechanic ✨",
        {}, {}
        });

    // 7: Search workshop
    story.push_back({
        "You find blueprints of a large device labeled ONLY HOPE.\n"
        "It seems unfinished. A generator hums softly beneath the floor.",
        {"Activate the generator", "Leave before something goes wrong"},
        {12, 13}
        });

    // 8: Inspect statue — ending
    story.push_back({
        "You touch the statue.\n"
        "Its eyes flare, and the plaza fills with ancient whispering voices.\n"
        "The city awakens—but not in the way you hoped.\n\n"
        "✨ Ending: Echoes of the King ✨",
        {}, {}
        });

    // 9: Tavern
    story.push_back({
        "Inside the tavern, a warm fire burns despite the city's abandonment.\n"
        "A menu lies open on the counter, names written in dust.",
        {"Call out to see if anyone is here", "Sit and warm your hands"},
        {14, 15}
        });

    // 10: Take key — ending
    story.push_back({
        "You take the key. The figure nods.\n"
        "The city rumbles. Time begins moving again.\n"
        "People awaken from the stasis.\n\n"
        "✨ Ending: The Key to Dawn ✨",
        {}, {}
        });

    // 11: Refuse key
    story.push_back({
        "The figure sighs.\n"
        "\"Then you are not ready. The city will wait another century.\"\n"
        "The window seals shut, trapping you inside.",
        {"Search for another exit", "Pound on the sealed window"},
        {16, 17}
        });

    // 12: Generator — ending
    story.push_back({
        "You flip the switch.\n"
        "A massive pulse of energy erupts, enveloping the city in light.\n"
        "When it fades, Asterfall is restored to its glory.\n\n"
        "✨ Ending: Rebirth of Asterfall ✨",
        {}, {}
        });

    // 13: Leave workshop — ending
    story.push_back({
        "You step outside just before the workshop collapses.\n"
        "The city swallows the workshop whole.\n\n"
        "✨ Ending: Survivor's Instinct ✨",
        {}, {}
        });

    // 14: Call out — ending
    story.push_back({
        "Your voice echoes.\n"
        "A shadowy figure rises behind the bar.\n"
        "\"We've been waiting for someone brave enough to return.\"\n\n"
        "✨ Ending: The Tavern of Souls ✨",
        {}, {}
        });

    // 15: Warm hands — ending
    story.push_back({
        "As you warm your hands, you feel at peace.\n"
        "The fire grows brighter until the room melts into light.\n\n"
        "✨ Ending: Peaceful Fade ✨",
        {}, {}
        });

    // 16: Search for exit — ending
    story.push_back({
        "You find a hidden ladder leading to the roof.\n"
        "The stars above swirl into a gateway.\n\n"
        "✨ Ending: Wanderer of the Sky ✨",
        {}, {}
        });

    // 17: Pound on window — ending
    story.push_back({
        "Your fists strike the window—\n"
        "and the glass opens like water, pulling you through.\n\n"
        "✨ Ending: The Window Between Worlds ✨",
        {}, {}
        });

    // ---------------------------------------------------------------
    // GAME LOOP — navigates the story tree until reaching an ending.
    // ---------------------------------------------------------------
    int current = 0;

    while (true) {
        StoryNode& node = story[current];

        blockText(node.text);

        // If no options, story ends here.
        if (node.options.empty()) {
            slowPrint("THE END.\n");
            break;
        }

        // Show options
        for (int i = 0; i < node.options.size(); i++) {
            cout << "  " << (i + 1) << ") ";
            slowPrint(node.options[i], 5);
        }

        int choice = getChoice(node.options.size());
        current = node.nextNodes[choice];  // Move to next node
    }

    slowPrint("Thanks for playing!");
    return 0;
}
