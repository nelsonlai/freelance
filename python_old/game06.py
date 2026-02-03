import pygame
import sys

pygame.init()

# Screen setup
WIDTH, HEIGHT = 600, 600
TILE = 40
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Maze Escape")

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (200, 0, 0)
GREEN = (0, 200, 0)
BLUE = (0, 0, 255)

clock = pygame.time.Clock()
font = pygame.font.Font(None, 48)

# Maze layout (1 = wall, 0 = empty)
maze = [
    "1111111111",
    "1000000001",
    "1011111101",
    "1010000101",
    "1010110101",
    "1010100101",
    "1011101101",
    "1000000001",
    "1111111101",
    "1111111111"
]

# Player position (grid coordinates)
player_x, player_y = 1, 1

# Exit position
exit_x, exit_y = 8, 7

def draw_maze():
    for row, line in enumerate(maze):
        for col, char in enumerate(line):
            rect = pygame.Rect(col*TILE, row*TILE, TILE, TILE)
            if char == "1":
                pygame.draw.rect(screen, RED, rect)
            else:
                pygame.draw.rect(screen, WHITE, rect)
    # Exit
    pygame.draw.rect(screen, GREEN, (exit_x*TILE, exit_y*TILE, TILE, TILE))

def show_message(message):
    text = font.render(message, True, BLUE)
    screen.blit(text, (WIDTH//2 - text.get_width()//2, HEIGHT//2 - text.get_height()//2))
    pygame.display.flip()
    pygame.time.wait(2500)

# Main loop
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    keys = pygame.key.get_pressed()
    new_x, new_y = player_x, player_y
    if keys[pygame.K_LEFT]:
        new_x -= 1
    if keys[pygame.K_RIGHT]:
        new_x += 1
    if keys[pygame.K_UP]:
        new_y -= 1
    if keys[pygame.K_DOWN]:
        new_y += 1

    # Check collision with walls
    if maze[new_y][new_x] == "0":
        player_x, player_y = new_x, new_y

    # Check win condition
    if player_x == exit_x and player_y == exit_y:
        screen.fill(WHITE)
        show_message("You Escaped!")
        pygame.quit()
        sys.exit()

    # Draw everything
    screen.fill(BLACK)
    draw_maze()
    pygame.draw.rect(screen, BLUE, (player_x*TILE, player_y*TILE, TILE, TILE))
    pygame.display.flip()
    clock.tick(10)