#include "recorder.h"
using namespace std;
using namespace boost::program_options;

// Maybe just use explicit string specifier.
// TODO: Python-style array printing.
/*namespace std {
    template <typename T>
    std::ostream& operator<<(std::ostream &os, const std::vector<T> &vec) {
        for (const auto &i : vec)
            os << i << " ";
        return os;
    }
}*/

int wmain(int argc, wchar_t *argv[]) {
    bool do_debug, do_cbt, do_wndproc, do_mouse, do_keyboard;

    options_description desc("Options");
    desc.add_options()
        ("help,h",
            "Help message")
        ("threads,t",
            value<vector<int>>()
                ->multitoken()
                ->default_value(vector<int>{0}, "0"),
            "Process/thread IDs to watch (0 is all)")
        ("debug,d", bool_switch(&do_debug),
            "All hookable events via debug hook")
        ("cbt,c", bool_switch(&do_debug),
            "Window manager message events")
        ("wndproc,w", bool_switch(&do_wndproc),
            "Application message events")
        ("mouse,m", bool_switch(&do_mouse),
            "Application level mouse events")
        ("keyboard,k", bool_switch(&do_keyboard),
            "Application level keyboard events");
    
    // Drops argv[0] if there is more than one argument, also
    // does not do globbing.
    //int argc;
    //wchar_t **argv = CommandLineToArgvW(lpCmdLine, &argc);

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << endl;
    }

    auto tids = vm["threads"].as<vector<int>>();
    vector<int> events;
    if (do_debug) events.push_back(WH_DEBUG);
    if (do_cbt) events.push_back(WH_CBT);
    if (do_wndproc) events.push_back(WH_CALLWNDPROC);
    if (do_mouse) events.push_back(WH_MOUSE);
    if (do_keyboard) events.push_back(WH_KEYBOARD);

    for (const auto &t : events)
        std::cout << t << endl;

    if (!events.size()) {
        std::cout << "No events to hook" << endl;
        exit(-1);
    }

    return 0;
}