#include <stdio.h>

int main()
{
    int n, obstacle_numbers, q_y, q_x, i, obstacle_x, obstacle_y;
    scanf("%d %d", &n, &obstacle_numbers);
    scanf("%d %d", &q_x, &q_y);
    
    // Set default max value for horizontal and vertical values
    int q_x_y_difference = q_x - q_y;
    int coordinate_combination = q_x + q_y;
    int max_distance_left_x = 1;
    int max_distance_left_y = q_y;
    int max_distance_right_x = n;
    int max_distance_right_y = q_y;
    int max_distance_bottom_x = q_x;
    int max_distance_bottom_y = 1;
    int max_distance_top_x = q_x;
    int max_distance_top_y = n;
    
    // Initialize max diagonal value
    int max_distance_diagonal_left_top_x;
    int max_distance_diagonal_left_top_y;
    int max_distance_diagonal_left_bottom_x;
    int max_distance_diagonal_left_bottom_y;
    int max_distance_diagonal_right_top_x;
    int max_distance_diagonal_right_top_y;
    int max_distance_diagonal_right_bottom_x;
    int max_distance_diagonal_right_bottom_y;
    
    // Set max value for all diagonals
    if(q_x_y_difference > 0){
        max_distance_diagonal_left_bottom_x = 1 + q_x_y_difference;
        max_distance_diagonal_left_bottom_y = 1;
        max_distance_diagonal_right_top_x = n;
        max_distance_diagonal_right_top_y = n - q_x_y_difference;
    } else {
        max_distance_diagonal_left_bottom_x = 1;
        max_distance_diagonal_left_bottom_y = 1 - q_x_y_difference;
        max_distance_diagonal_right_top_x = n + q_x_y_difference;
        max_distance_diagonal_right_top_y = n;
    } 

    if(coordinate_combination > n){
        max_distance_diagonal_left_top_x = coordinate_combination - n;
        max_distance_diagonal_left_top_y = n;
        max_distance_diagonal_right_bottom_x = n;
        max_distance_diagonal_right_bottom_y = coordinate_combination - n;
    } else {
        max_distance_diagonal_left_top_x = 1;
        max_distance_diagonal_left_top_y = coordinate_combination - 1;
        max_distance_diagonal_right_bottom_x = coordinate_combination - 1;
        max_distance_diagonal_right_bottom_y = 1;
    }
    
    // Add one value for each side, so we don't need to adjust more logic if the value is being replaced by new obstacle, just subtract the answer by one for each side (-8)
    max_distance_left_x--;
    max_distance_right_x++;
    max_distance_bottom_y--;
    max_distance_top_y++;
    
    max_distance_diagonal_left_top_x--;
    max_distance_diagonal_left_top_y++;
    max_distance_diagonal_left_bottom_x--;
    max_distance_diagonal_left_bottom_y--;
    max_distance_diagonal_right_top_x++;
    max_distance_diagonal_right_top_y++;
    max_distance_diagonal_right_bottom_x++;
    max_distance_diagonal_right_bottom_y--;
    
    // Input each obstacle and compare with maximum value in each side
    int ox_oy_difference, obstacle_coordinate_combination;
    for(i = 0; i < obstacle_numbers; i++){
        scanf("%d %d", &obstacle_x, &obstacle_y);
        obstacle_coordinate_combination = obstacle_x + obstacle_y;
        ox_oy_difference = obstacle_x - obstacle_y;
        if(obstacle_x == q_x){
        	if(obstacle_y > q_y){
        		if(obstacle_y < max_distance_top_y){
        			max_distance_top_x = obstacle_x;
        			max_distance_top_y = obstacle_y;
        		}
        	} else {
        		if(obstacle_y > max_distance_bottom_y){
        			max_distance_bottom_x = obstacle_x;
        			max_distance_bottom_y = obstacle_y;
        		}
        	}
        } else if(obstacle_y == q_y) {
        	if(obstacle_x > q_x){
        		if(obstacle_x < max_distance_right_x){
        			max_distance_right_x = obstacle_x;
        			max_distance_right_y = obstacle_y;
        		}
        	} else {
        		if(obstacle_x > max_distance_left_x){
        			max_distance_left_x = obstacle_x;
        			max_distance_left_y = obstacle_y;
        		}
        	}
        } else if(q_x_y_difference == ox_oy_difference) {
        	if(obstacle_y > q_y){
        		if(obstacle_y < max_distance_diagonal_right_top_y){
        			max_distance_diagonal_right_top_x = obstacle_x;
        			max_distance_diagonal_right_top_y = obstacle_y;
        		}
        	} else {
        		if(obstacle_y > max_distance_diagonal_left_bottom_y){
        			max_distance_diagonal_left_bottom_x = obstacle_x;
        			max_distance_diagonal_left_bottom_y = obstacle_y;
        		}
        	}
        } else if(coordinate_combination == obstacle_coordinate_combination) {
        	if(obstacle_y > q_y){
        		if(obstacle_y < max_distance_diagonal_left_top_y){
        			max_distance_diagonal_left_top_x = obstacle_x;
        			max_distance_diagonal_left_top_y = obstacle_y;
        		}
        	} else {
        		if(obstacle_y > max_distance_diagonal_right_bottom_y){
        			max_distance_diagonal_right_bottom_x = obstacle_x;
        			max_distance_diagonal_right_bottom_y = obstacle_y;
        		}
        	}
        }   
    }

    // Count moveable square in diagonal, horizontal and vertical
    int right_diagonal = max_distance_diagonal_right_top_y - max_distance_diagonal_left_bottom_y;
    int left_diagonal = max_distance_diagonal_left_top_y - max_distance_diagonal_right_bottom_y;
    int horizontal = max_distance_top_y - max_distance_bottom_y;
    int vertical = max_distance_right_x - max_distance_left_x;
    int squares_number =  right_diagonal + left_diagonal + horizontal + vertical;
    
    // Print the answer
    printf("%d\n", squares_number - 8);
    
    return 0;
}
