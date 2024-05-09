#include "interface.h"
#include "registers.h"

#include <argparse/argparse.hpp>
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>

static bool set_logging_level(const std::string &level_name) {
  auto level = magic_enum::enum_cast<spdlog::level::level_enum>(level_name);
  if (level.has_value()) {
    spdlog::set_level(level.value());
    return true;
  }
  return false;
}

auto main(int argc, char *argv[]) -> int {
  spdlog::set_level(spdlog::level::info);

  argparse::ArgumentParser program("aceboy", "0.0.1");

  program.add_argument("--log-level")
      .help("Set the verbosity for logging")
      .default_value(std::string("info"))
      .nargs(1);

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  const std::string level = program.get("--log-level");
  if (!set_logging_level(level)) {
    std::cerr << fmt::format("Invalid argument \"{}\" - allowed options: "
                             "{{trace, debug, info, warn, err, critical, off}}",
                             level)
              << std::endl;
    std::cerr << program;
    return 1;
  }

  // Interface interface;
  // interface.run();

  Registers regs;
  regs.reset();

  regs.set8(kRegA, 0b110001);
  regs.flags.set(kFlagZ, 0);
  regs.flags.set(kFlagN, 1);
  regs.flags.set(kFlagH, 1);
  regs.flags.set(kFlagC, 1);

  spdlog::info("flag z: {}", regs.flags.get(kFlagZ));
  spdlog::info("flag n: {}", regs.flags.get(kFlagN));
  spdlog::info("flag h: {}", regs.flags.get(kFlagH));
  spdlog::info("flag c: {}", regs.flags.get(kFlagC));
  spdlog::info("af: {:016b}", regs.get16(kRegAF));
  spdlog::info("af: {:08b}|{:08b}", regs.get8(kRegA), regs.get8(kRegF));

  spdlog::info("Exiting.");

  return 0;
}
