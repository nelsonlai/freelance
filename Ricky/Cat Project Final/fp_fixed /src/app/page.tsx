import Image from "next/image";
import styles from "./page.module.css";
import Link from "next/link";


export default function Home() {
  return (
    <div>
      <header className="Header">
      <div className="logo">
        <div className="logo-circle">
          <div className="cat-face"></div>
        </div>
        <h1>PawMatch</h1>
      </div>

      <nav>
        <a href="#features">Features</a>
        <a href="#how">How It Works</a>
        <a href="#mission">Mission</a>
        <a href="#benefits">Benefits</a>
      </nav>

      <nav>
     <Link href="/cat-questionnaire" className="btn-primary">
            Join Platform
          </Link>
      <Link href="/login" className="btn-primary">
            Login
          </Link>
      </nav>
    </header>

   
    <section className="hero">
      <div className="hero-content">
        <div className="hero-text">
          <span className="hero-badge">Ethical Cat Breeding Platform</span>
          <h2>Responsible Cat Matching Through Science & Transparency</h2>
          <p>
            We enable natural, ethical cat pairing for owners seeking suitable
            matches. Our comprehensive database and AI‑powered tools support
            healthier litters while opposing mass breeding and kitten mills.
          </p>
          <div className="hero-feature-list">
            <span> ✅ Health Records</span>
            <span> ✅ Genetic Testing</span>
            <span> ✅ AI Previews</span>
          </div>
        <p className="hero-extra">
      We hope you can share more valuable information about your cats — health,
      personality, care tips, and breeding experiences.  
      Let’s exchange knowledge and help every cat live a healthier, happier life.
    </p>
          <div className="hero-buttons">


          <a
  href="https://docs.google.com/forms/d/e/1FAIpQLScPPwaHDG4b_HV-rFNSyjcdy31ESjHCbuKeIfb7w-Bn292KgQ/viewform"
  className="cta-btn"
  target="_blank"
  rel="noopener noreferrer"
>
  Share Your Experience
</a>

          </div>
        </div>

        <div className="hero-image">
  <Image
  src="/image/cats.jpg"
  alt="Cat family"
  width={500}
  height={450}
  priority
/>

         
        </div>
      </div>
    </section>

   {/* =====✅ PLATFORM FEATURES SECTION ===== */}
<section className="features" id="features">
  <div className="features-container">
    <span className="section-badge">Platform Features</span>
    <h2>Everything You Need for Responsible Breeding</h2>
    <p className="subtitle">
      Our comprehensive platform provides the tools and data necessary for
      making informed, ethical breeding decisions.
    </p>

    <div className="features-row">
      <div className="feature-card">
        <div className="icon">
          <i className="fas fa-database"></i>
        </div>
        <h3>Comprehensive Database</h3>
        <p>
          Maintain detailed profiles with health records, pedigree, temperament
          assessments, and genetic test results for informed pairing.
        </p>
      </div>

      <div className="feature-card">
        <div className="icon">
          <i className="fas fa-cat"></i>
        </div>
        <h3>AI Kitten Previews</h3>
        <p>
          Advanced AI technology generates visual previews of potential kittens
          by combining parent features such as coat patterns, eye color, and
          genetic traits.
        </p>
      </div>

      <div className="feature-card">
        <div className="icon">
          <i className="fas fa-notes-medical"></i>
        </div>
        <h3>Health & Genetic Records</h3>
        <p>
          Complete health documentation and genetic testing results prevent
          hereditary diseases and ensure healthier litters for future
          generations.
        </p>
      </div>

      <div className="feature-card">
        <div className="icon">
          <i className="fas fa-dna"></i>
        </div>
        <h3>Smart Matching</h3>
        <p>
          Science‑guided algorithms help find the best matches based on genetics,
          temperament, and breeding goals for responsible pairing.
        </p>
      </div>
    </div>
  </div>
</section>





    {/* ===== HOW IT WORKS ===== */}
<section className="process" id="how">
  <div className="process-container">
   
    <h2>How PawMatch Works</h2>
    <p className="subtitle">
      Four simple steps to find the perfect match for your cat while ensuring
      ethical breeding practices.
    </p>

    <div className="process-grid">
      <div className="process-card">
        <div className="number">1</div>
        <h3>Create Profile</h3>
        <p>
          Upload your cat's information including match records, pedigree,
          temperament, and genetic test results.
        </p>
      </div>

      <div className="process-card">
        <div className="number">2</div>
        <h3>Browse Matches</h3>
        <p>
          Search our database of verified cats and use our smart matching system
          to find compatible partners.
        </p>
      </div>

      <div className="process-card">
        <div className="number">3</div>
        <h3>Preview Offspring</h3>
        <p>
          Use our AI tool to visualize potential kitten characteristics before
          making breeding decisions.
        </p>
      </div>

      <div className="process-card">
        <div className="number">4</div>
        <h3>Connect & Breed</h3>
        <p>
          Connect with verified owners and coordinate responsible breeding with
          complete transparency.
        </p>
      </div>
    </div>
  </div>
</section>

{/* =====MISSION SECTION ===== */}
<section className="mission" id="mission">
  <div className="mission-container">
    {/* === LEFT TEXT AREA === */}
    <div className="mission-content">
      <span className="badge">Our Mission</span>
      <h2>Promoting Animal Welfare Through Ethical Breeding</h2>
      <p>
        We believe that every cat deserves to be bred responsibly with
        consideration for their health, genetics, and wellbeing. Our platform
        empowers responsible breeding operations and kitten mills by providing
        transparent, science-based matching tools.
      </p>
      <p>
        By connecting responsible owners and maintaining comprehensive health
        profiles, we help reduce hereditary diseases, lower veterinary costs,
        and ensure healthier futures for all cats.
      </p>

      <div className="mission-features">
        <div className="mcard">
          <div className="micon"><i className="fas fa-hand-holding-heart"></i></div>
          <div>
            <h3>Responsible Matches</h3>
            <p>
              We prioritize animal welfare with respectful, ethical pairing
              decisions that put the health and wellbeing of cats first.
            </p>
          </div>
        </div>

        <div className="mcard">
          <div className="micon"><i className="fas fa-dna"></i></div>
          <div>
            <h3>Science‑Guided Breeding</h3>
            <p>
              Leverage genetic data and health analytics to reduce hereditary
              diseases and promote healthier outcomes for all litters.
            </p>
          </div>
        </div>

        <div className="mcard">
          <div className="micon"><i className="fas fa-file-medical-alt"></i></div>
          <div>
            <h3>Transparent Data</h3>
            <p>
              Complete transparency in breeding records prevents unethical
  
            </p>
          </div>
        </div>
      </div>
    </div>

    {/* === RIGHT IMAGE AREA === */}
    <div className="mission-image">
      <Image
        src="/close-up-adorable-kittens.jpg"
        alt="Two fluffy kittens"
        width={500}
        height={700}
        priority
        style={{ objectFit: 'cover', borderRadius: 'var(--radius)' }}
      />
    </div>
  </div>
</section>

{/* === BENEFITS SECTION === */}
<section className="benefits" id="benefits">
  <div className="benefits-container">
    <h2>Benefits for Cat Owners & Breeders</h2>
    <p className="subtitle">
      Join our community of responsible cat owners committed to ethical breeding
      practices and healthier feline futures.
    </p>

    <div className="benefits-grid">
      <div className="benefit-card">
        <i className="fas fa-dna"></i>
        <span>Reduce risk of inherited genetic diseases</span>
      </div>
      <div className="benefit-card">
        <i className="fas fa-paw"></i>
        <span>Lower veterinary costs with healthier offspring</span>
      </div>
      <div className="benefit-card">
        <i className="fas fa-shield-virus"></i>
        <span>Prevent infectious diseases during mating</span>
      </div>
      <div className="benefit-card">
        <i className="fas fa-notes-medical"></i>
        <span>Access verified health and pedigree data</span>
      </div>
      <div className="benefit-card">
        <i className="fas fa-heart"></i>
        <span>Support ethical breeding practices</span>
      </div>
      <div className="benefit-card">
        <i className="fas fa-users"></i>
        <span>Connect with responsible cat owners</span>
      </div>
    </div>

    
    <Link href="/cat-questionnaire" className="cta-btn">
            Start Matching Today
          </Link>
   
  </div>
</section>

{/* === FOOTER SECTION  === */}
<footer className="site-footer">
  <div className="footer-container">
    <p className="footer-highlight">
      This is a pet matching platform created by Ricky, where every furry friend deserves a happy home!
    </p>

    <p>
     We promote responsible cat breeding through science, transparency, and ethics. Together, let’s ensure our pets grow up healthy and happy, all thanks to human creativity and love! 💖
    </p>
  
  </div>
</footer>

      
    </div>
  );
}
