# ft_nm
Project ft_nm of 42.
nm is a UNIX function that examin binary files.
In this project we have to write a program in C who does the same things (with bonus flags).
For this project we use ELF Format (struct and DEFINE) with a map.

## How nm work

nm is a function that list the symbols from objects file, if there isnt any arguments he will take a.out
He show each symbol in a different link with somes informations :
value type name

Value is the hexadicemal value of the symbol

Type is the type of the symbol who will depend on the type, bind and flags (most of the lowercase arer local except u v and w)

Name is the name of the symbol, if it has a version information associated it will displayed if there isnt the version string is displayed

### Header struct
With the map we can cast it in the ELF struct Ehdr (64 or 32 bits) who is defined like this :

```c
#define EI_NIDENT 16
typedef struct
{
	unsigned char	e_ident[EI_NIDENT];
	uint16_t		e_type;
	uint16_t		e_machine;
	uint32_t		e_version;
	ElfN_Addr		e_entry;
	ElfN_Off		e_phoff;
	ElfN_Off		e_shoff;
	uint32_t		e_flags;
	uint16_t		e_ehsize;
	uint16_t		e_phentsize;
	uint16_t		e_phnum;
	uint16_t		e_shentsize;
	uint16_t		e_shnum;
	uint16_t		e_shstrndx;
} ElfN_Ehdr;
```

- `e_ident` is the magics number (the 4 first must be in order : 0x7f, E, L and F), next are other informations, like 32 or 64 bits, version...
(for more information about ELF Identification click [here](https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblj/index.html#chapter6-35342))

- `e_type` is the type of the file

- `e_machine` specifies the architecture of the file

- `e_version` identifies the object file (EV_NONE who is equal to 0 is invalid)

- `e_entry` is the value of the entry of the program adress (typical for a main), the value is 0 is there is not

- `e_phoff` is the program header table file offset in bytes

- `e_shoff` is the section header table file offset in bytes

- `e_flags` is the processor flags

- `e_ehsize` is the header size in bytes

- `e_phentsize` is the program header table entry size

- `e_phnum` is the program header table entry count

- `e_shentsize` is the section header table entry size

- `e_shnum` is the section header table entry count

- `e_shstrndx` is the section header string table index

(for more information about ELF Header click [here](https://docs.oracle.com/cd/E19683-01/816-1386/chapter6-43405/index.html))

### Section struct

Once we have the Ehdr struct, map can be cast in an other struct from ELF named Shdr (32 or 64 bits) who is defined like this :

```c
typedef struct
{
	Elf64_Word		sh_name;
	Elf64_Word		sh_type;
	Elf64_Xword		sh_flags;
	Elf64_Addr		sh_addr;
	Elf64_Off		sh_offset;
	Elf64_Xword		sh_size;
	Elf64_Word		sh_link;
	Elf64_Word		sh_info;
	Elf64_Xword		sh_addralign;
	Elf64_Xword		sh_entsize;
} Elf64_Shdr;

```
- `sh_name` is the section name
- `sh_type` is the section type
- `sh_flags` is the section flags
- `sh_addr` is the section virtual addr at execution
- `sh_offset` is the section file offset
- `sh_size` is the section size in bytes
- `sh_link` is the section link to an other section
- `sh_info` is the section information whose depend on section type
- `sh_addralign` is the section alignement constraints
- `sh_entsize` if the section hold a table it's the entry size

(for more information about ELF Section click [here](https://docs.oracle.com/cd/E19683-01/816-1386/chapter6-94076/index.html))

### Symbol struct

```c
typedef struct
{
	Elf64_Word		st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf64_Half		st_shndx;
	Elf64_Addr		st_value;
	Elf64_Xword		st_size;
} Elf64_Sym;
```

- `st_name` is the symbol name
- `st_info` is the symbol type and attributes
- `st_other` is the symbol visibility
- `st_shndx` is the symbol entry defined by the section
- `st_value` is the symbol value
- `st_size` is the symbol size

(for more information about sym, click [here](https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblj/index.html#chapter6-79797))

## Explanation of the program

When the program start we need to check the entry (arguments, flags).
If there isnt any arguments, the program try a.out, if there is multiple argument we do the program on all of them.

To do that we need to open and map the file, once the map is created and add is a struct we go in nm function.

With the map created we cast it in ELF header and check if it's a valid file and if it's 64 or 32 bits and go to the function made for.
(there isn't any difference in 64 and 32 bits except the struct).

Once the header is parsed we do a cast from the Header e_shoff to have the section.
With the section we get the .symtab and .strtab and keep them for later.
After that we get the symbols and set a variable for the name.

For each symbol we set them in a variable that will keep information of section who is valid for nm.
To finish we need to check the flags is there is a need to remove lines or sort them in a specific order

## Bonus

The bonus of the project are the flags : a, p, u, g and r
r reverse sort the list
p doesnt sort the list
a add the debug file (found in symtab)
u show the undefined only
g show the extern only

Somes flags remove effects of other flags :
r and p together r will never be used
g a and u only one will be used it have an order wich is u g and a (-gau will show -u, -ga will show -g)
