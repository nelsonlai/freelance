import pygame       # pygame.org to see the details of pygame modules
import random       # random module
import sys          # sys module, system

# Initialize pygame
pygame.init()   # Initialize display for pygame
pygame.mixer.init()  # Initialize sound for pygame

# Load sound effects
hit_sound = pygame.mixer.Sound("hit.wav")
dodge_sound = pygame.mixer.Sound("dodge.wav")

# Screen settings
WIDTH = 1000        # Width (X) of the game window, pixels
HEIGHT = 720       # Height (Y)of the game window, pixels
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Dodge the Falling Blocks")

# Clock and fonts
clock = pygame.time.Clock()
font = pygame.font.SysFont(None, 40)

# Colors
WHITE = (255, 255, 255)     # R,G,B
BLACK = (0, 0, 0)
RED   = (255, 0, 0)
BLUE  = (0, 0, 255)

# Player settings
player_width = 50
player_height = 10
player_x = WIDTH // 2 - player_width // 2
player_y = HEIGHT - 40
player_speed = 7

# Enemy block settings
block_width = 50
block_height = 50
block_speed = 5
blocks = []

# Score
score = 0

# Function to draw text
def draw_text(text, font, color, surface, x, y):
    textobj = font.render(text, True, color)
    rect = textobj.get_rect()
    rect.topleft = (x, y)
    surface.blit(textobj, rect)

# Function to add a new block
def add_block():
    x_pos = random.randint(0, WIDTH - block_width)
    blocks.append(pygame.Rect(x_pos, 0, block_width, block_height))

# Game loop
running = True
ADD_BLOCK_EVENT = pygame.USEREVENT + 1
pygame.time.set_timer(ADD_BLOCK_EVENT, 1000)

while running:
    screen.fill(WHITE)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == ADD_BLOCK_EVENT:
            add_block()

    # Get keys
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and player_x > 0:
        player_x -= player_speed
    if keys[pygame.K_RIGHT] and player_x < WIDTH - player_width:
        player_x += player_speed

    # Draw player
    player_rect = pygame.Rect(player_x, player_y, player_width, player_height)
    pygame.draw.rect(screen, BLUE, player_rect)

    # Move and draw blocks
    for block in blocks[:]:
        block.y += block_speed
        pygame.draw.rect(screen, RED, block)    # rect -> (x, y, width, height) rectangle

        if block.colliderect(player_rect):
            hit_sound.play()
            draw_text("Game Over!", font, RED, screen, WIDTH // 2 - 80, HEIGHT // 2)
            pygame.display.flip()
            pygame.time.wait(2000)
            pygame.quit()
            sys.exit()

        if block.y > HEIGHT:
            blocks.remove(block)
            dodge_sound.play()
            score += 1

    # Show score
    draw_text(f"Score: {score}", font, BLACK, screen, 10, 10)

    pygame.display.flip()
    clock.tick(60) 