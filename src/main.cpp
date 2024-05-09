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

  regs.set8(kRegA, 1);
  regs.set8(kRegF, 0b10001111);
  regs.set8(kRegB, 3);
  regs.set8(kRegC, 4);
  regs.set8(kRegD, 5);
  regs.set8(kRegE, 6);
  regs.set8(kRegH, 7);
  regs.set8(kRegL, 8);
  regs.sp = 123;
  regs.pc = 45678;

  regs.flags.set(kFlagZ, 1);
  regs.flags.set(kFlagN, 0);
  regs.flags.set(kFlagH, 1);
  regs.flags.set(kFlagC, 0);

  spdlog::info("flag z: {}", regs.flags.get(kFlagZ));
  spdlog::info("flag n: {}", regs.flags.get(kFlagN));
  spdlog::info("flag h: {}", regs.flags.get(kFlagH));
  spdlog::info("flag c: {}", regs.flags.get(kFlagC));

  spdlog::info("a: {:08b} = {}", regs.get8(kRegA), regs.get8(kRegA));
  spdlog::info("f: {:08b} = {}", regs.get8(kRegF), regs.get8(kRegF));
  spdlog::info("af: {:016b} = {}", regs.get16(kRegAF), regs.get16(kRegAF));

  spdlog::info("b: {:08b} = {}", regs.get8(kRegB), regs.get8(kRegB));
  spdlog::info("c: {:08b} = {}", regs.get8(kRegC), regs.get8(kRegC));
  spdlog::info("bc: {:016b} = {}", regs.get16(kRegBC), regs.get16(kRegBC));

  spdlog::info("d: {:08b} = {}", regs.get8(kRegD), regs.get8(kRegD));
  spdlog::info("e: {:08b} = {}", regs.get8(kRegE), regs.get8(kRegE));
  spdlog::info("de: {:016b} = {}", regs.get16(kRegDE), regs.get16(kRegDE));

  spdlog::info("h: {:08b} = {}", regs.get8(kRegH), regs.get8(kRegH));
  spdlog::info("l: {:08b} = {}", regs.get8(kRegL), regs.get8(kRegL));
  spdlog::info("hl: {:016b} = {}", regs.get16(kRegHL), regs.get16(kRegHL));

  spdlog::info("sp: {:08b} = {}", regs.sp, regs.sp);
  spdlog::info("pc: {:08b} = {}", regs.pc, regs.pc);

  regs.set16(kRegAF, 4567);
  regs.set16(kRegBC, 6678);
  regs.set16(kRegDE, 1193);
  regs.set16(kRegHL, 2356);

  spdlog::info("af: {:016b} = {}", regs.get16(kRegAF), regs.get16(kRegAF));
  spdlog::info("bc: {:016b} = {}", regs.get16(kRegBC), regs.get16(kRegBC));
  spdlog::info("de: {:016b} = {}", regs.get16(kRegDE), regs.get16(kRegDE));
  spdlog::info("hl: {:016b} = {}", regs.get16(kRegHL), regs.get16(kRegHL));

  spdlog::info("Exiting.");

  return 0;
}
