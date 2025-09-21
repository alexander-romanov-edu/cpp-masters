#include <cstdlib>
#include <stwine/string_twine.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <print>

namespace po = boost::program_options;
int main(int argc, char **argv) try {
  auto desc = po::options_description{"Allowed options"};
  std::vector<std::string> to_concat(5);
  desc.add_options()("help", "Produce help message");
  desc.add_options()("input-word", po::value(&to_concat)->composing(),
                     "Input word");
  po::positional_options_description pos_desc;
  pos_desc.add("input-word", 5);
  auto vm = po::variables_map{};
  po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(pos_desc)
                .run(),
            vm);
  if (vm.count("help")) {
    std::cout << desc << "\n";
    return EXIT_SUCCESS;
  }
  po::notify(vm);
  if (!vm.count("input-word"))
    return EXIT_SUCCESS;
  to_concat.resize(5);
  std::println("{}", mcpp::string_twine(to_concat.at(0))
                         .concat(to_concat.at(1))
                         .concat(to_concat.at(2))
                         .concat(to_concat.at(3))
                         .concat(to_concat.at(4))
                         .str());
} catch (std::exception &e) {
  std::println("error: {}", e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println("unknown internal error");
  return EXIT_FAILURE;
}
