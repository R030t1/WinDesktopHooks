#include "recorder.h"
using namespace std;
using namespace boost::program_options;

int wmain(int argc, wchar_t *argv[]) {
    try {
        options_description desc("Options");
        desc.add_options()
            ("help,h",
                "Help message")
            ("tid,t", value<vector<int>>()->multitoken(),
                "Process/thread IDs to watch");
        
        // Drops argv[0] if there is more than one argument, also
        // does not do globbing.
        //int argc;
        //wchar_t **argv = CommandLineToArgvW(lpCmdLine, &argc);

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout << desc << endl;
        } else if (vm.count("tid")) {
            auto tids = vm["tid"].as<vector<int>>();
            for (const auto &t : tids)
                std::cout << t << endl;
        }
    } catch (const error &ex) {
        std::cerr << ex.what() << endl;
    }
    return 0;
}