#include "fat.h"
#include "sd.h"
#include "rprintf.h"
#include "serial.h"
#include "clibfuncs.h"

struct boot_sector *bs;
char bootSector[512]; // allocate a global array to store boot sector
char rootBuffer[512];
struct root_directory_entry *fat;

unsigned int root_sector;

int fatInit(){
	char buffer[10];
	sd_readblock(0, bootSector, 1);
	bs = bootSector;
	int k = 0;
	while (bs->fs_type[k] !=  ' ' || k >= 8){
		esp_printf(putc,"%c", bs->fs_type[k]);
		buffer[k] = bs->fs_type[k];
		k++;
		buffer[k] = 0;
	}
	if (bs->boot_signature = 0xaa55) {
		esp_printf(putc, "Validated  boot signiture \n");
	}
	if (strcmp(buffer, "FAT16")) {
		esp_printf(putc, "It is FAT16 \n \n");
	}
	esp_printf(putc,"Bytes per sector = %d \n" ,bs->bytes_per_sector);
	esp_printf(putc,"Sectors per cluster = %d \n" ,bs->num_sectors_per_cluster);
	esp_printf(putc,"Num Fat Tables = %d \n" ,bs->num_fat_tables); 
	int root_sector_value = (bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors;
	esp_printf(putc, "Root sector value = %d \n", root_sector_value);
}

struct file *file_open;
void fatOpen(struct file* f, char* filename) {
	int t_sectors = bs->num_root_dir_entries;
	int t = 1;
	char buffer[10];
	int root_sector_value = ((bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors);
	esp_printf(putc, "BOOT SECTOR = %x\n", bs);
	sd_readblock(root_sector_value, rootBuffer, 1);
	fat = rootBuffer;
	while (t < t_sectors) {
		int k = 0;
		while (k < 8) {
			esp_printf(putc, "%c", fat->file_name[k]);
			if (fat->file_name[k] != ' '){
				buffer[k] = fat->file_name[k];
			}
			k++;
		}
		buffer[7] = 0;

		if (strcmp(buffer, filename) == 0) {
			esp_printf(putc, "Buffer is equal \n");
			f->rde = *fat;
			f->start_cluster = fat->cluster;
			return;
		}
		esp_printf(putc, "\n%s\n", buffer);
		t++;
		fat++;
	}
}


void fatRead(struct file* f, char buffer, int bytes_read) {
	int root_sector_value = ((bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors);
	esp_printf(putc, "\nRDE Cluster --> %d \n", f->rde.cluster);

	int first_root_dir = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat) + ((bs->num_root_dir_entries * 32) + (bs->bytes_per_sector - 1)) / bs->bytes_per_sector;
	int first_sector = first_root_dir + ((f->rde.cluster - 2) * bs->num_sectors_per_cluster);
	
	sd_readblock(first_sector,rootBuffer,1);

	esp_printf(putc, "Readblock --> %s \n", rootBuffer);
	esp_printf(putc, "First root dir --> %d \n", first_root_dir);
	esp_printf(putc, "First sector --> %d \n", first_sector);
}
