
#include <filesystem>
#include <fstream>

#include "argtable3.h"
#include "constants.hpp"
#include "machine/machine.hpp"
#include "spdlog/spdlog.h"
#include "utils/args/arg_slice.h"

void init_machine(char **memory_file, uint64_t entrypoint, SlicePair* slices, uint8_t slices_count) {
    spdlog::info("Initializing machine with memory_file = {} and entrypoint = {}", *memory_file, entrypoint);

    auto machine = new Machine();

    spdlog::info("Setting up machine's memory");
    auto machine_memory = machine->getMemory();

    // Load the memory bin
    spdlog::info("Loading {}", *memory_file);
    std::ifstream input( *memory_file, std::ios::binary );

    if(input.fail()) {
      throw std::logic_error("Error while opening the input file");
    }

    auto memory_file_size = std::filesystem::file_size(*memory_file);

    MachineMemorySlice* memory_file_slice = machine_memory->addSlice(
        memory_file_size, MachineMemorySliceFlag::MMSF_EXECUTABLE, 0x0);
    auto* base =
        reinterpret_cast<uint8_t *>(memory_file_slice->getHostAddress());
    while(!input.eof())
    {
      *base = input.get();
      base++;
    }
    // TODO: Lock the page (On Windows: https://learn.microsoft.com/fr-fr/windows/win32/api/memoryapi/nf-memoryapi-virtuallock, Linux: https://linux.die.net/man/2/mlock)

    // Create slices
    spdlog::info("Loading {} slices", slices_count);
    for(size_t slice = 0; slice < slices_count; slice++) {
      SlicePair* slice_pair = &slices[slice];
      spdlog::debug("Creating slice {} with {} bytes at {}", slice, slice_pair->size, slice_pair->start);
      machine_memory->addSlice(slice_pair->size, MachineMemorySliceFlag::MMSF_EXECUTABLE, slice_pair->start);
    }


    spdlog::info("Stopping machine");
    machine->stop();

    spdlog::info("Freeing resources");
    delete machine;
}


int main(int argc, char **argv)
{
    uint64_t entrypoint = 0x0;
    char** memory_file;


    /* Define the allowable command line options, collecting them in argtable[] */
    struct arg_file *base_memory_file     = arg_file1("m", "memory_file",        "<input>", "Load a memory file into the machine's memory");
    struct arg_int *entrypoint_address = arg_int1(NULL, "entrypoint",         "Set the entrypoint address (0x0 by default)", "");
    struct arg_slice *slices  = arg_slicen("s", "slice", "<start>,<size>", 1, 10, "specify slice start and size (entrypoint_address.g., 32kb,0x8000)");
    struct arg_lit *help  = arg_lit0(NULL,"help",       "print this help and exit");
    struct arg_lit *vers  = arg_lit0(NULL,"version",    "print version information and exit");
    struct arg_str *strs  = arg_strn(NULL,NULL,"STRING",0,argc+2,NULL);
    struct arg_end *end   = arg_end(20);
    void* argtable[] = {base_memory_file, entrypoint_address,slices,help,vers,strs,end};
    int exitcode=0;
    int nerrors;

    /* verify the argtable[] entries were allocated sucessfully */
    if (arg_nullcheck(argtable) != 0)
    {
        /* NULL entries were detected, some allocations must have failed */
        printf("%s: insufficient memory\n", PROGNAME);
        exitcode=1;
        goto exit;
    }

    /* Parse the command line as defined by argtable[] */
    nerrors = arg_parse(argc,argv,argtable);

    /* special case: '--help' takes precedence over error reporting */
    if (help->count > 0)
    {
        printf("Usage: %s", PROGNAME);
        arg_print_syntax(stdout,argtable,"\n");
        printf("Echo the STRINGs to standard output.\n\n");
        arg_print_glossary(stdout,argtable,"  %-10s %s\n");
        exitcode=0;
        goto exit;
    }

    /* special case: '--version' takes precedence error reporting */
    if (vers->count > 0)
    {
        printf("P64ASM, émulateur de machine.\n");
        printf("2024, Raphaël FLEURY-LE VESO\n");
        exitcode=0;
        goto exit;
    }

    /* If the parser returned any errors then display them and exit */
    if (nerrors > 0)
    {
        /* Display the error details contained in the arg_end struct.*/
        arg_print_errors(stdout,end,PROGNAME);
        printf("Try '%s --help' for more information.\n",PROGNAME);
        exitcode=1;
        goto exit;
    }
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Starting up {} ({})", PROGNAME, PROGVER);


    // Check if arg is set
    entrypoint = *entrypoint_address->ival;
    memory_file = const_cast<char **>(base_memory_file->filename);

    init_machine(memory_file, entrypoint, slices->slices, slices->count);

    exit:
    /* deallocate each non-null entry in argtable[] */
    arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));

    return exitcode;
}