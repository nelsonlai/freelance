import pygame
import random
import sys

# Initialize pygame
pygame.init()
pygame.mixer.init()

# Load sounds
catch_sound = pygame.mixer.Sound("catch.wav")
miss_sound = pygame.mixer.Sound("miss.wav")

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

# Star
star_radius = 15
star_speed = 5
stars = []

# Score
score = 0

# Create a new star
def create_star():
    x = random.randint(star_radius, WIDTH - star_radius)
    y = -star_radius
    stars.append([x, y])

# Draw everything
def draw():
    screen.fill(WHITE)

    # Draw basket
    pygame.draw.rect(screen, BLUE, (basket_x, basket_y, basket_width, basket_height))

    # Draw stars
    for x, y in stars:
        pygame.draw.circle(screen, YELLOW, (x, y), star_radius)

    # Draw score
    score_text = font.render(f"Score: {score}", True, BLACK)
    screen.blit(score_text, (10, 10))

    pygame.display.flip()

# Game loop
ADD_STAR_EVENT = pygame.USEREVENT + 1
pygame.time.set_timer(ADD_STAR_EVENT, 1000)

running = True
while running:
    clock.tick(60)

    # Event handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == ADD_STAR_EVENT:
            create_star()

    # Key press handling
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and basket_x > 0:
        basket_x -= basket_speed
    if keys[pygame.K_RIGHT] and basket_x < WIDTH - basket_width:
        basket_x += basket_speed

    # Move stars
    for star in stars[:]:
        star[1] += star_speed

        # Check if caught
        if (basket_y <= star[1] + star_radius <= basket_y + basket_height and
            basket_x <= star[0] <= basket_x + basket_width):
            stars.remove(star)
            score += 1
            catch_sound.play()

        # Remove if it falls off screen
        elif star[1] > HEIGHT:
            stars.remove(star)
            miss_sound.play()

    # Draw everything
    draw()

pygame.quit()
sys.exit()