#pragma warning(push, 0)
#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdio.h>
#pragma(pop)

#pragma warning(disable :5045)

typedef struct
{
  uint32_t x;
  uint32_t y;
} start_coord_t;

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{
  //TODO: Implement this function!
  /*
    1. Allocate a grid of size grid_dim x grid_dim using VirtualAlloc.
  */
 static uint8_t *grid = NULL;
 static int first_call = 1;

  if (!grid)
  {
    grid = (uint8_t *)VirtualAlloc(NULL, grid_dim * grid_dim, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    //printf("Failed to allocate memory for the grid.\n");
    for (uint32_t i = 0; i < grid_dim * grid_dim; i++)
    {
      grid[i] = 0;
    }
  }
  if(first_call)
  {
    for (uint32_t i = 0; i < initial_point_count; i++)
    {
      start_coord_t c = initial_points[i];
      grid[c.y * grid_dim + c.x] = 1;
    }
    first_call = 0;
    return grid;  
  }  
  uint8_t *new_grid = (uint8_t *)VirtualAlloc(NULL, grid_dim * grid_dim, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if (!new_grid)
  {
    return NULL;
  }
  for (uint32_t i = 0; i < grid_dim * grid_dim; i++)
  {
    new_grid[i] = 0;
  }
  
  for (uint32_t y = 0; y < grid_dim; y++)
  {
    for (uint32_t x = 0; x < grid_dim; x++)
    {
      uint8_t live_neighbors = 0;
      uint8_t current_cell = grid[y * grid_dim + x];
      for (int dy = -1; dy <= 1; dy++)
      {
        for (int dx = -1; dx <= 1; dx++)
        {
          if (dx == 0 && dy == 0)
            continue; 
          // uint32_t nx = (x + dx + grid_dim) % grid_dim;
          // uint32_t ny = (y + dy + grid_dim) % grid_dim;
          int32_t temp_x = (int32_t)x + dx;
          int32_t temp_y = (int32_t)y + dy;
          
          uint32_t nx = ((temp_x % (int32_t)grid_dim) + grid_dim) % grid_dim;
          uint32_t ny = ((temp_y % (int32_t)grid_dim) + grid_dim) % grid_dim;
         
          live_neighbors += grid[ny * grid_dim + nx];
        }
      }
      if (current_cell == 1)
      {
        if (live_neighbors < 2 || live_neighbors > 3)
          new_grid[y * grid_dim + x] = 0;
        else
          new_grid[y * grid_dim + x] = 1;
      }
      else
      {
        if (live_neighbors == 3)
          new_grid[y * grid_dim + x] = 1;
        else
          new_grid[y * grid_dim + x] = 0;
      }
    }
  }
  // VirtualFree(grid, 0, MEM_RELEASE);
  grid = new_grid;
  return new_grid;
}

