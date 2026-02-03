import pygame
import random
import sys      ## for system timer

# Initialize pygame
pygame.init()

# Screen settings
WIDTH, HEIGHT = 800, 800
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Space Shooter")

# Colors    - computer color system is RGB
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
BLACK = (0, 0, 0)

clock = pygame.time.Clock()

# Player
player_width, player_height = 60, 20
player_x = WIDTH // 2 - player_width // 2
player_y = HEIGHT - 50
player_speed = 8

# Bullets
bullets = []
bullet_speed = 8

# Meteors
meteors = []
meteor_speed = 4
meteor_size = 40

# Score
score = 0
font = pygame.font.Font(None, 36)

def create_meteor():
    x = random.randint(0, WIDTH - meteor_size)
    y = 0
    meteors.append([x, y])

# Main loop
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        # Shooting bullets
        if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
            bullets.append([player_x + player_width // 2 - 5, player_y])

    # Move player
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and player_x > 0:
        player_x -= player_speed
    if keys[pygame.K_RIGHT] and player_x < WIDTH - player_width:
        player_x += player_speed

    # Move bullets
    for bullet in bullets:
        bullet[1] -= bullet_speed

    # Remove bullets off screen
    bullets = [b for b in bullets if b[1] > 0]

    # Create meteors
    if random.random() < 0.03:
        create_meteor()

    # Move meteors
    for meteor in meteors:
        meteor[1] += meteor_speed

    # Check collisions (bullet vs meteor)
    bullet_rects = [pygame.Rect(b[0], b[1], 10, 20) for b in bullets]
    meteor_rects = [pygame.Rect(m[0], m[1], meteor_size, meteor_size) for m in meteors]

    new_meteors = []
    for meteor_rect, meteor in zip(meteor_rects, meteors):
        hit = False
        for bullet_rect, bullet in zip(bullet_rects, bullets):
            if meteor_rect.colliderect(bullet_rect):
                score += 1
                bullets.remove(bullet)
                hit = True
                break
        if not hit:
            new_meteors.append(meteor)
    meteors = new_meteors

    # Check collisions (meteor vs player)
    player_rect = pygame.Rect(player_x, player_y, player_width, player_height)
    for meteor in meteors:
        if player_rect.colliderect(pygame.Rect(meteor[0], meteor[1], meteor_size, meteor_size)):
            screen.fill(BLACK)
            text = font.render(f"Game Over! Score: {score}", True, WHITE)
            screen.blit(text, (WIDTH//2 - 150, HEIGHT//2))
            pygame.display.flip()
            pygame.time.wait(3000)
            pygame.quit()
            sys.exit()

    # Remove meteors off screen
    meteors = [m for m in meteors if m[1] < HEIGHT]

    # Draw everything
    screen.fill(BLACK)
    pygame.draw.rect(screen, BLUE, player_rect)
    for b in bullets:
        pygame.draw.rect(screen, YELLOW, (b[0], b[1], 10, 20))
    for m in meteors:
        pygame.draw.rect(screen, RED, (m[0], m[1], meteor_size, meteor_size))

    # Draw score
    score_text = font.render(f"Score: {score}", True, WHITE)
    screen.blit(score_text, (10, 10))

    pygame.display.flip()
    clock.tick(60)