#include "recorder.h"
using namespace std;
using namespace boost::program_options;

// TODO: Template type.
// Maybe just use explicit string specifier.
/*namespace std {
    std::ostream& operator<<(std::ostream &os, const std::vector<int> &vec) {
        for (const auto &i : vec)
            os << i << " ";
        return os;
    }
}*/

int wmain(int argc, wchar_t *argv[]) {
    try {
        options_description desc("Options");
        desc.add_options()
            ("help,h",
                "Help message")
            ("thread-ids,t",
                value<vector<int>>()
                    ->multitoken()
                    ->default_value(vector<int>{0}, "0"),
                "Process/thread IDs to watch (0 is all)");
        
        // Drops argv[0] if there is more than one argument, also
        // does not do globbing.
        //int argc;
        //wchar_t **argv = CommandLineToArgvW(lpCmdLine, &argc);

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout << desc << endl;
        } else if (vm.count("thread-ids")) {
            auto tids = vm["thread-ids"].as<vector<int>>();
            for (const auto &t : tids)
                std::cout << t << endl;
        }
    } catch (const error &ex) {
        std::cerr << ex.what() << endl;
    }
    return 0;
}