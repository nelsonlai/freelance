import pygame
import random
import sys
import time

# Initialize pygame
pygame.init()
pygame.mixer.init()

# Load sounds
catch_sound = pygame.mixer.Sound("catch.wav")
miss_sound = pygame.mixer.Sound("miss.wav")
bomb_sound = pygame.mixer.Sound("bomb.wav")

# Set up display
WIDTH = 500
HEIGHT = 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Catch the Falling Stars")

# Colors
WHITE = (255, 255, 255)
BLUE = (0, 102, 204)
YELLOW = (255, 255, 0)
BLACK = (0, 0, 0)
RED = (255, 0, 0)

# Fonts
font = pygame.font.SysFont(None, 36)

# Clock
clock = pygame.time.Clock()

# Basket
basket_width = 80
basket_height = 20
basket_x = WIDTH // 2 - basket_width // 2
basket_y = HEIGHT - 40
basket_speed = 8

# Star and Bomb settings
star_radius = 15
bomb_radius = 15
fall_speed = 5
stars = []
bombs = []

# Score and Time
score = 0
game_duration = 30  # seconds
start_time = time.time()

# Create a new star or bomb
def create_falling_object():
    x = random.randint(star_radius, WIDTH - star_radius)
    if random.random() < 0.7:  # 70% chance of star
        stars.append([x, -star_radius])
    else:  # 30% chance of bomb
        bombs.append([x, -bomb_radius])

# Draw everything
def draw():
    screen.fill(WHITE)

    # Draw basket
    pygame.draw.rect(screen, BLUE, (basket_x, basket_y, basket_width, basket_height))

    # Draw stars
    for x, y in stars:
        pygame.draw.circle(screen, YELLOW, (x, y), star_radius)

    # Draw bombs
    for x, y in bombs:
        pygame.draw.circle(screen, RED, (x, y), bomb_radius)

    # Draw score
    score_text = font.render(f"Score: {score}", True, BLACK)
    screen.blit(score_text, (10, 10))

    # Draw timer
    time_left = max(0, game_duration - int(time.time() - start_time))
    timer_text = font.render(f"Time: {time_left}", True, BLACK)
    screen.blit(timer_text, (WIDTH - 140, 10))

    pygame.display.flip()

# Game loop
ADD_OBJECT_EVENT = pygame.USEREVENT + 1
pygame.time.set_timer(ADD_OBJECT_EVENT, 800)

running = True
while running:
    clock.tick(60)

    # Check if time is up
    elapsed = time.time() - start_time
    if elapsed >= game_duration:
        running = False
        continue

    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == ADD_OBJECT_EVENT:
            create_falling_object()

    # Key press handling
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and basket_x > 0:
        basket_x -= basket_speed
    if keys[pygame.K_RIGHT] and basket_x < WIDTH - basket_width:
        basket_x += basket_speed

    # Move and check stars
    for star in stars[:]:
        star[1] += fall_speed
        if (basket_y <= star[1] + star_radius <= basket_y + basket_height and
            basket_x <= star[0] <= basket_x + basket_width):
            stars.remove(star)
            score += 1
            catch_sound.play()
        elif star[1] > HEIGHT:
            stars.remove(star)
            miss_sound.play()

    # Move and check bombs
    for bomb in bombs[:]:
        bomb[1] += fall_speed
        if (basket_y <= bomb[1] + bomb_radius <= basket_y + basket_height and
            basket_x <= bomb[0] <= basket_x + basket_width):
            bomb_sound.play()
            draw()
            pygame.time.wait(1000)
            running = False
            break
        elif bomb[1] > HEIGHT:
            bombs.remove(bomb)

    # Draw everything
    draw()

# End screen
screen.fill(WHITE)
end_text = font.render(f"Game Over! Your score: {score}", True, BLACK)
screen.blit(end_text, (WIDTH // 2 - 160, HEIGHT // 2))
pygame.display.flip()
pygame.time.wait(3000)
pygame.quit()
sys.exit()