#include <stdio.h>
#include <stdbool.h>

void defaultListValue(int *list_value, int amount)
{
    for(int i = 0; i < amount; ++i)
        list_value[i] = 0;
}

int notificationAmountEvenType(int notification_sent, int index, int list_value[], int expenditure[], int number, int center) 
{
    int first_median = 0;
    for(int j = 0; j < 202; j++){
        if(list_value[j]) {
            number += list_value[j];
            if(number >= center){
                if(first_median){
                    if(expenditure[index] >= (first_median + j)){
                        notification_sent++;
                    }
                    center--;
                    break;
                } else {
                    center++;
                    if(number >= center){
                        if(expenditure[index] >= j * 2){
                            notification_sent++;
                        }
                        center--;
                        break;
                    }
                    first_median = j;
                }
            }
        }
    }
    return notification_sent;
}

int notificationAmountOddType(int notification_sent, int index, int list_value[], int expenditure[], int number, int center) 
{
    int first_median = 0;
    for(int j = 0; j < 202; j++){
        if(list_value[j]) {
            number += list_value[j];
            if(number >= center) {
                if(expenditure[index] >= j * 2){
                    notification_sent++;
                } 
                break;
            }
        }
    }
    return notification_sent;
}

int executeEvenFraudulent(int n, int notification_sent, int start, int list_value[], int expenditure[], int center)
{
    int number;
    for (int i = start; i < n; i++) {
        number = 0;
        notification_sent = notificationAmountEvenType(notification_sent, i, list_value, expenditure, number, center);
        list_value[expenditure[i]]++;
        list_value[expenditure[i-start]]--;
    }
    return notification_sent;
}

int executeOddFraudulent(int n, int notification_sent, int start, int list_value[], int expenditure[], int center)
{
    int number;
    for (int i = start; i < n; i++) {
        number = 0;
        notification_sent = notificationAmountOddType(notification_sent, i, list_value, expenditure, number, center);
        list_value[expenditure[i]]++;
        list_value[expenditure[i-start]]--;
    }
    return notification_sent;
}

int executeFraudulent(bool even, int n, int notification_sent, int d, int list_value[], int expenditure[], int center)
{
    if(even) notification_sent = executeEvenFraudulent(n, notification_sent, d, list_value, expenditure, center);
    else notification_sent = executeOddFraudulent(n, notification_sent, d, list_value, expenditure, center);
    return notification_sent;
}

int main()
{
    int n, d, i, j, notification_sent;
    scanf("%d %d", &n, &d);
    
    // Set default center position and flag even
    int center = d/2 + 1;
    bool even = false;
    if(d % 2 == 0){
        center--;
        even = true;
    } 
    
    int list_value[201], expenditure[n], number;
    
    // Set zero to all lookback days
    defaultListValue(list_value, 201);
    
    // Input expenditure list
    for(i = 0; i< n; i++) scanf("%d", &expenditure[i]);
    
    // Adding first lookback days
    for(i = 0; i < d; i++) list_value[expenditure[i]]++;
    
    // Execute 
    notification_sent = executeFraudulent(even, n, 0, d, list_value, expenditure, center);
    
    printf("%d", notification_sent);

    return 0;
}
