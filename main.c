#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int randInt();

int main(){
  int fd = open("nums.txt", O_RDWR | O_CREAT, 644);
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  int nums[11];
  printf("Generating random numbers:\n");
  int i = 0;
  for (; i < 10; i++) nums[i] = randInt();
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  i = 0;
  for (; i < 10; i++) printf("random %d: %d\n", i, nums[i]);
  printf("Writing numbers to file.\n");
  write(fd, nums, sizeof(nums));
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  printf("Verification that numbers are the same (by reading):\n");
  read(fd, nums, sizeof(nums));
  i = 0;
  for (; i < 10; i++) printf("random %d: %d\n", i, nums[i]);
  close(fd);
  return 0;
}

int randInt(){
  int fd = open("/dev/random", O_RDONLY);
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  int * buff;
  read(fd, buff, sizeof(int));
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  close(fd);
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  return *buff;
}
