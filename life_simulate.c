#pragma warning(push, 0)
#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
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
  static uint8_t *map = NULL; // Pointer to the grid map
  static uint32_t stored_dimension = 0; // Stored dimension of the grid
  static uint32_t current_map = 0; // Current map index (0 or 1)
  static int first_call = 1; // Flag to check if it's the first call
  // size_t total_size; // Total size of the grid map
  uint32_t map_size; // Size of the grid
  uint8_t *current; // Pointer to the current grid
  uint8_t *next; // Pointer to the next grid
  uint8_t live_neighbors; // Count of live neighbors
  uint8_t current_cell; // Current cell state

  // Allocate memory for the grid map if it's the first call or if the dimension has changed
  if( map == NULL || stored_dimension != grid_dim)
  {
      // total_size = 2 * grid_dim * grid_dim * sizeof(uint8_t);
      map = calloc(2 * grid_dim * grid_dim, sizeof(uint8_t));
      if(!map)
        return NULL;
      stored_dimension = grid_dim; // Update stored dimension
      current_map = 0; // Reset current map index        
  }
  map_size = grid_dim * grid_dim; // Calculate size of the grid
  current = map + (current_map * map_size); // Set pointer to the current grid
  if (first_call)
  {
    for(uint32_t i = 0; i < initial_point_count; i++)
    {
      start_coord_t c = initial_points[i];
      map[c.y * grid_dim + c.x] = 1; // Set initial live cells
    }
    first_call = 0; // Clear the first call flag
    return current; // Return the current grid
  }
  next = map + ((1 - current_map) * map_size); // Set pointer to the next grid
  for (uint32_t i = 0; i < grid_dim * grid_dim; i++)
  {
    next[i] = 0; // Clear the next grid
  }
<<<<<<< HEAD
  // Iterate over each cell in the grid
=======

  // int y_dim = 0;
  // int x_dim = 0;

  //   for (;y_dim < grid_dim && current[y_dim * grid_dim + x_dim] == 0; y_dim++)
  //   {
  //     for (x_dim = 0; x_dim < grid_dim && current[y_dim * grid_dim + x_dim] == 0; x_dim++)
  //     {
  //       ;
  //     }
  //   }
  //   y_dim -= grid_dim;

>>>>>>> dba1a647213d4f61480bb9bef5935a353c0e7d75
  for (uint32_t y = 0; y < grid_dim; y++)
  {
    for (uint32_t x = 0; x < grid_dim; x++)
    {
      live_neighbors = 0; // next to the main cells 
      current_cell = current[y * grid_dim + x]; // Get the current cell 
      // Check all 8 neighbors
      for (int g_y = -1; g_y <= 1; g_y++)
      {
        for (int g_x = -1; g_x <= 1; g_x++)
        {
          // if its the cell in the middle, skip it
          if (g_x == 0 && g_y == 0)
            continue;
          // Calculate neighbor coordinates with wrapping
          uint32_t wrap_x = (x + g_x  + grid_dim) % grid_dim;
          uint32_t wrap_y = (y + g_y  + grid_dim) % grid_dim;
          live_neighbors += current[wrap_y * grid_dim + wrap_x]; // Count live neighbors
        }
        if (current_cell == 1)
        {
          if (live_neighbors < 2 || live_neighbors > 3)
            next[y * grid_dim + x] = 0;
          else
            next[y * grid_dim + x] = 1;
        }
        else
        {
          if (live_neighbors == 3)
            next[y * grid_dim + x] = 1;
          else
            next[y * grid_dim + x] = 0;
        }
      }
    }
  }
  current_map = 1 - current_map; // Switch to the next grid
  return map + (current_map * map_size); // Return the current grid
}



// ================ version 1 ===================
// uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
// {
//   //TODO: Implement this function!
//  static uint8_t *grid = NULL;
//  static int first_call = 1;
//  static uint32_t current_grid = 0;
//  static uint32_t store_grid_dim = 0;

//   if (!grid || store_grid_dim != grid_dim)
//   {
//     if(grid)
//       VirtualFree(grid, 0, MEM_RELEASE);
//     size_t total_size = 2 * grid_dim * grid_dim * sizeof(uint8_t);
//     grid = (uint8_t *)VirtualAlloc(NULL, total_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//     if (!grid)
//       return NULL;
//     for (uint32_t i = 0; i < grid_dim * grid_dim; i++)
//     {
//       grid[i] = 0;
//     }
//     current_grid = 0;
//     store_grid_dim = grid_dim;
//     first_call = 1;
//   }
//   uint32_t grid_size = grid_dim * grid_dim;
//   uint8_t *current = grid + (current_grid * grid_size);
//   uint8_t *next = grid + ((1 - current_grid) * grid_size);

//   if(first_call)
//   {
//     for (uint32_t i = 0; i < initial_point_count; i++)
//     {
//       start_coord_t c = initial_points[i];
//       current[c.y * grid_dim + c.x] = 1;
//     }
//     first_call = 0;
//     return current;  
//   }
//   for (uint32_t i = 0; i < grid_dim * grid_dim; i++)
//   {
//     next[i] = 0;
//   }
//   // for (uint32_t i = 0; i < grid_dim * grid_dim; i++)
//   // {
//   //   next[i] = 0;
//   // }

//   for (uint32_t y = 0; y < grid_dim; y++)
//   {
//     for (uint32_t x = 0; x < grid_dim; x++)
//     {
//       uint8_t live_neighbors = 0;
//       uint8_t current_cell = current[y * grid_dim + x];
//       for (int dy = -1; dy <= 1; dy++)
//       {
//         for (int dx = -1; dx <= 1; dx++)
//         {
//           if (dx == 0 && dy == 0)
//             continue; 
//           uint32_t nx = (x + dx + grid_dim) % grid_dim;
//           uint32_t ny = (y + dy + grid_dim) % grid_dim;
//           // int32_t temp_x = (int32_t)x + dx;
//           // int32_t temp_y = (int32_t)y + dy;
          
//           // uint32_t nx = ((temp_x % (int32_t)grid_dim) + grid_dim) % grid_dim;
//           // uint32_t ny = ((temp_y % (int32_t)grid_dim) + grid_dim) % grid_dim;
         
//           live_neighbors += current[ny * grid_dim + nx];
//         }
//       }
//       if (current_cell == 1)
//       {
//         if (live_neighbors < 2 || live_neighbors > 3)
//           next[y * grid_dim + x] = 0;
//         else
//           next[y * grid_dim + x] = 1;
//       }
//       else
//       {
//         if (live_neighbors == 3)
//           next[y * grid_dim + x] = 1;
//         else
//           next[y * grid_dim + x] = 0;
//       }
//     }
//   }
//   current_grid = 1 - current_grid;
//   return grid + (current_grid * grid_size);
// }

