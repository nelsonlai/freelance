from datetime import datetime

from flask import Flask, render_template, request

app = Flask(__name__)


SUPPORTED_LANGUAGES = {
    "en": {"label": "English", "html_lang": "en"},
    "it": {"label": "Italiano", "html_lang": "it"},
    "fr": {"label": "Francais", "html_lang": "fr"},
    "es": {"label": "Espanol", "html_lang": "es"},
    "zh-tw": {"label": "繁體中文", "html_lang": "zh-Hant"},
}


TRANSLATIONS = {
    "en": {
        "meta_title": "Palazzo di Firenze | Luxury Boutique Hotel Florence",
        "hotel_name": "Palazzo di Firenze",
        "nav_about": "About",
        "nav_rooms": "Rooms",
        "nav_amenities": "Amenities",
        "nav_location": "Location",
        "book_now": "Book Now",
        "hero_title": "Experience the Soul of Florence",
        "hero_subtitle": "A luxurious sanctuary in the heart of the Renaissance city, where 16th-century history meets contemporary Italian elegance.",
        "hero_cta_primary": "Book Your Stay",
        "hero_cta_secondary": "Explore Suites",
        "about_kicker": "A Legacy of Elegance",
        "about_title": "Quintessentially Italian",
        "about_text": "Step into a world of refined Italian hospitality. Palazzo di Firenze occupies a meticulously restored 16th-century estate, offering a poetic blend of historic charm and contemporary luxury. Our commitment to the art of living ensures every guest experiences the timeless beauty of the Renaissance from their own private sanctuary.",
        "stats_labels": ["Heritage Site", "Concierge", "Dining", "Views"],
        "rooms_title": "Rooms & Suites",
        "rooms_subtitle": "Exquisite comfort in every detail",
        "rooms": [
            {
                "name": "Classic Room",
                "description": "Quiet elegance with artisan furniture and Carrara marble bathrooms.",
                "price": "From EUR 450",
            },
            {
                "name": "Duomo Suite",
                "description": "Unparalleled views of Brunelleschi's Dome from your private terrace.",
                "price": "From EUR 890",
            },
            {
                "name": "Renaissance Suite",
                "description": "Original 16th-century frescoes and grand high ceilings for a royal stay.",
                "price": "From EUR 1,200",
            },
        ],
        "view_details": "View Details",
        "amenities_title": "Exceptional Amenities",
        "amenities_subtitle": "Curated experiences for the modern traveler",
        "amenities": [
            {
                "icon": "restaurant",
                "name": "Gourmet Breakfast",
                "description": "Traditional Florentine pastries and organic local delights served daily.",
            },
            {
                "icon": "deck",
                "name": "Rooftop Terrace",
                "description": "Signature cocktails with 360-degree panoramic views of the city skyline.",
            },
            {
                "icon": "concierge",
                "name": "Concierge Service",
                "description": "Exclusive access to Uffizi tickets and private wine tours in Tuscany.",
            },
            {
                "icon": "spa",
                "name": "Spa & Wellness",
                "description": "A sanctuary of tranquility featuring Roman-inspired baths and treatments.",
            },
        ],
        "location_kicker": "Our Neighborhood",
        "location_title": "The Heart of Florence",
        "location_text": "Located within the restricted ZTL zone, we offer a peaceful escape just steps away from the city's most iconic treasures.",
        "landmarks": [
            {"name": "Uffizi Gallery", "distance": "4 minutes walking distance through historic piazzas."},
            {"name": "Ponte Vecchio", "distance": "6 minutes to the world's most famous jewelry bridge."},
            {"name": "Piazza della Signoria", "distance": "2 minutes from our front door."},
        ],
        "footer_text": "Experience the ultimate in Florentine luxury. Our doors are open to those who seek the extraordinary in the city of flowers.",
        "contact_title": "Contact",
        "quick_links_title": "Quick Links",
        "quick_links": ["Private Events", "Gift Vouchers", "Careers", "Media Kit"],
        "privacy": "Privacy",
        "terms": "Terms",
        "copyright_suffix": "All rights reserved.",
        "language_label": "Language",
    },
    "it": {
        "meta_title": "Palazzo di Firenze | Hotel Boutique di Lusso a Firenze",
        "hotel_name": "Palazzo di Firenze",
        "nav_about": "Chi Siamo",
        "nav_rooms": "Camere",
        "nav_amenities": "Servizi",
        "nav_location": "Posizione",
        "book_now": "Prenota Ora",
        "hero_title": "Vivi l'Anima di Firenze",
        "hero_subtitle": "Un rifugio di lusso nel cuore della citta rinascimentale, dove la storia del XVI secolo incontra l'eleganza italiana contemporanea.",
        "hero_cta_primary": "Prenota il Tuo Soggiorno",
        "hero_cta_secondary": "Scopri le Suite",
        "about_kicker": "Un'Eredita di Eleganza",
        "about_title": "Autenticamente Italiano",
        "about_text": "Entra in un mondo di raffinata ospitalita italiana. Palazzo di Firenze occupa una dimora del XVI secolo restaurata con cura, offrendo una poetica unione tra fascino storico e lusso contemporaneo. Il nostro impegno per l'arte del vivere assicura a ogni ospite la bellezza senza tempo del Rinascimento.",
        "stats_labels": ["Sito Storico", "Concierge", "Ristorazione", "Vista Duomo"],
        "rooms_title": "Camere e Suite",
        "rooms_subtitle": "Comfort esclusivo in ogni dettaglio",
        "rooms": [
            {
                "name": "Camera Classica",
                "description": "Eleganza discreta con arredi artigianali e bagni in marmo di Carrara.",
                "price": "Da EUR 450",
            },
            {
                "name": "Suite Duomo",
                "description": "Vista impareggiabile sulla Cupola del Brunelleschi dalla tua terrazza privata.",
                "price": "Da EUR 890",
            },
            {
                "name": "Suite Rinascimento",
                "description": "Affreschi originali del XVI secolo e soffitti maestosi per un soggiorno regale.",
                "price": "Da EUR 1.200",
            },
        ],
        "view_details": "Vedi Dettagli",
        "amenities_title": "Servizi Eccezionali",
        "amenities_subtitle": "Esperienze curate per il viaggiatore moderno",
        "amenities": [
            {
                "icon": "restaurant",
                "name": "Colazione Gourmet",
                "description": "Pasticceria fiorentina tradizionale e delizie locali biologiche ogni giorno.",
            },
            {
                "icon": "deck",
                "name": "Terrazza Panoramica",
                "description": "Cocktail d'autore con vista panoramica a 360 gradi sulla citta.",
            },
            {
                "icon": "concierge",
                "name": "Servizio Concierge",
                "description": "Accesso esclusivo ai biglietti degli Uffizi e tour privati del vino in Toscana.",
            },
            {
                "icon": "spa",
                "name": "Spa e Benessere",
                "description": "Un santuario di tranquillita con bagni e trattamenti ispirati all'antica Roma.",
            },
        ],
        "location_kicker": "Il Nostro Quartiere",
        "location_title": "Il Cuore di Firenze",
        "location_text": "Nel cuore della zona ZTL, offriamo un rifugio tranquillo a pochi passi dai tesori piu iconici della citta.",
        "landmarks": [
            {"name": "Galleria degli Uffizi", "distance": "A 4 minuti a piedi tra piazze storiche."},
            {"name": "Ponte Vecchio", "distance": "A 6 minuti dal ponte orafo piu famoso del mondo."},
            {"name": "Piazza della Signoria", "distance": "A 2 minuti dalla nostra porta d'ingresso."},
        ],
        "footer_text": "Vivi il massimo del lusso fiorentino. Le nostre porte sono aperte a chi cerca l'eccezionale nella citta dei fiori.",
        "contact_title": "Contatti",
        "quick_links_title": "Link Rapidi",
        "quick_links": ["Eventi Privati", "Gift Card", "Carriere", "Media Kit"],
        "privacy": "Privacy",
        "terms": "Termini",
        "copyright_suffix": "Tutti i diritti riservati.",
        "language_label": "Lingua",
    },
    "fr": {
        "meta_title": "Palazzo di Firenze | Hotel Boutique de Luxe a Florence",
        "hotel_name": "Palazzo di Firenze",
        "nav_about": "A Propos",
        "nav_rooms": "Chambres",
        "nav_amenities": "Services",
        "nav_location": "Emplacement",
        "book_now": "Reserver",
        "hero_title": "Vivez l'Ame de Florence",
        "hero_subtitle": "Un sanctuaire luxueux au coeur de la cite Renaissance, ou l'histoire du XVIe siecle rencontre l'elegance italienne contemporaine.",
        "hero_cta_primary": "Reserver Votre Sejour",
        "hero_cta_secondary": "Decouvrir les Suites",
        "about_kicker": "Un Heritage d'Elegance",
        "about_title": "Quintessence Italienne",
        "about_text": "Entrez dans un univers d'hospitalite italienne raffinee. Palazzo di Firenze occupe une demeure du XVIe siecle restauree avec soin, alliant charme historique et luxe contemporain. Notre art de vivre permet a chaque hote de ressentir la beaute intemporelle de la Renaissance.",
        "stats_labels": ["Site Patrimonial", "Conciergerie", "Gastronomie", "Vues"],
        "rooms_title": "Chambres et Suites",
        "rooms_subtitle": "Un confort exquis dans chaque detail",
        "rooms": [
            {
                "name": "Chambre Classique",
                "description": "Elegance paisible avec mobilier artisanal et salles de bain en marbre de Carrare.",
                "price": "A partir de EUR 450",
            },
            {
                "name": "Suite Duomo",
                "description": "Vue incomparable sur le Dome de Brunelleschi depuis votre terrasse privee.",
                "price": "A partir de EUR 890",
            },
            {
                "name": "Suite Renaissance",
                "description": "Fresques originales du XVIe siecle et hauts plafonds majestueux pour un sejour royal.",
                "price": "A partir de EUR 1 200",
            },
        ],
        "view_details": "Voir les Details",
        "amenities_title": "Services Exceptionnels",
        "amenities_subtitle": "Des experiences pensees pour le voyageur moderne",
        "amenities": [
            {
                "icon": "restaurant",
                "name": "Petit Dejeuner Gourmet",
                "description": "Viennoiseries florentines traditionnelles et produits locaux bio servis chaque jour.",
            },
            {
                "icon": "deck",
                "name": "Terrasse Panoramique",
                "description": "Cocktails signature avec vue panoramique a 360 degres sur la ville.",
            },
            {
                "icon": "concierge",
                "name": "Service de Conciergerie",
                "description": "Acces exclusif aux billets des Offices et visites privees de vignobles toscans.",
            },
            {
                "icon": "spa",
                "name": "Spa et Bien-Etre",
                "description": "Un sanctuaire de serenite avec bains et soins inspires de la Rome antique.",
            },
        ],
        "location_kicker": "Notre Quartier",
        "location_title": "Le Coeur de Florence",
        "location_text": "Situe dans la zone ZTL, nous offrons un havre de paix a quelques pas des tresors emblématiques de la ville.",
        "landmarks": [
            {"name": "Galerie des Offices", "distance": "A 4 minutes a pied a travers les places historiques."},
            {"name": "Ponte Vecchio", "distance": "A 6 minutes du pont de joaillerie le plus celebre du monde."},
            {"name": "Piazza della Signoria", "distance": "A 2 minutes de notre porte d'entree."},
        ],
        "footer_text": "Vivez le sommet du luxe florentin. Nos portes sont ouvertes a ceux qui recherchent l'extraordinaire dans la ville des fleurs.",
        "contact_title": "Contact",
        "quick_links_title": "Liens Rapides",
        "quick_links": ["Evenements Prives", "Bons Cadeaux", "Carrieres", "Media Kit"],
        "privacy": "Confidentialite",
        "terms": "Conditions",
        "copyright_suffix": "Tous droits reserves.",
        "language_label": "Langue",
    },
    "es": {
        "meta_title": "Palazzo di Firenze | Hotel Boutique de Lujo en Florencia",
        "hotel_name": "Palazzo di Firenze",
        "nav_about": "Nosotros",
        "nav_rooms": "Habitaciones",
        "nav_amenities": "Servicios",
        "nav_location": "Ubicacion",
        "book_now": "Reservar",
        "hero_title": "Vive el Alma de Florencia",
        "hero_subtitle": "Un santuario de lujo en el corazon de la ciudad renacentista, donde la historia del siglo XVI se une con la elegancia italiana contemporanea.",
        "hero_cta_primary": "Reserva Tu Estancia",
        "hero_cta_secondary": "Explorar Suites",
        "about_kicker": "Un Legado de Elegancia",
        "about_title": "Esencialmente Italiano",
        "about_text": "Entra en un mundo de hospitalidad italiana refinada. Palazzo di Firenze ocupa una propiedad del siglo XVI restaurada con meticulosidad, combinando encanto historico y lujo contemporaneo. Nuestro compromiso con el arte de vivir garantiza una experiencia renacentista inolvidable para cada huesped.",
        "stats_labels": ["Sitio Historico", "Conserjeria", "Gastronomia", "Vistas"],
        "rooms_title": "Habitaciones y Suites",
        "rooms_subtitle": "Comodidad exquisita en cada detalle",
        "rooms": [
            {
                "name": "Habitacion Clasica",
                "description": "Elegancia serena con mobiliario artesanal y banos de marmol de Carrara.",
                "price": "Desde EUR 450",
            },
            {
                "name": "Suite Duomo",
                "description": "Vistas incomparables de la Cupula de Brunelleschi desde tu terraza privada.",
                "price": "Desde EUR 890",
            },
            {
                "name": "Suite Renacimiento",
                "description": "Frescos originales del siglo XVI y techos majestuosos para una estancia real.",
                "price": "Desde EUR 1.200",
            },
        ],
        "view_details": "Ver Detalles",
        "amenities_title": "Servicios Excepcionales",
        "amenities_subtitle": "Experiencias seleccionadas para el viajero moderno",
        "amenities": [
            {
                "icon": "restaurant",
                "name": "Desayuno Gourmet",
                "description": "Pasteleria florentina tradicional y delicias locales organicas cada dia.",
            },
            {
                "icon": "deck",
                "name": "Terraza Panoramica",
                "description": "Cocteles de autor con vistas panoramicas de 360 grados de la ciudad.",
            },
            {
                "icon": "concierge",
                "name": "Servicio de Conserjeria",
                "description": "Acceso exclusivo a entradas para los Uffizi y tours privados de vino en Toscana.",
            },
            {
                "icon": "spa",
                "name": "Spa y Bienestar",
                "description": "Un santuario de tranquilidad con banos y tratamientos inspirados en Roma.",
            },
        ],
        "location_kicker": "Nuestro Barrio",
        "location_title": "El Corazon de Florencia",
        "location_text": "En la zona ZTL, ofrecemos una escapada tranquila a pocos pasos de los tesoros mas iconicos de la ciudad.",
        "landmarks": [
            {"name": "Galeria Uffizi", "distance": "A 4 minutos a pie por plazas historicas."},
            {"name": "Ponte Vecchio", "distance": "A 6 minutos del puente joyero mas famoso del mundo."},
            {"name": "Piazza della Signoria", "distance": "A 2 minutos de nuestra puerta principal."},
        ],
        "footer_text": "Vive lo mejor del lujo florentino. Nuestras puertas estan abiertas para quienes buscan lo extraordinario en la ciudad de las flores.",
        "contact_title": "Contacto",
        "quick_links_title": "Enlaces Rapidos",
        "quick_links": ["Eventos Privados", "Bonos Regalo", "Carreras", "Media Kit"],
        "privacy": "Privacidad",
        "terms": "Terminos",
        "copyright_suffix": "Todos los derechos reservados.",
        "language_label": "Idioma",
    },
    "zh-tw": {
        "meta_title": "Palazzo di Firenze | 佛羅倫斯精品奢華飯店",
        "hotel_name": "Palazzo di Firenze",
        "nav_about": "關於我們",
        "nav_rooms": "客房",
        "nav_amenities": "設施",
        "nav_location": "位置",
        "book_now": "立即預訂",
        "hero_title": "感受佛羅倫斯的靈魂",
        "hero_subtitle": "坐落於文藝復興古城核心的奢華居所，讓十六世紀歷史與現代義式優雅完美交會。",
        "hero_cta_primary": "預訂您的住宿",
        "hero_cta_secondary": "探索套房",
        "about_kicker": "優雅傳承",
        "about_title": "純粹義式風華",
        "about_text": "走進精緻義式待客之道。Palazzo di Firenze 由十六世紀歷史建築修復而成，融合古典韻味與當代奢華。我們堅持生活美學，讓每位旅客都能在專屬空間感受文藝復興的永恆之美。",
        "stats_labels": ["歷史建築", "禮賓服務", "米其林餐飲", "主教堂景觀"],
        "rooms_title": "客房與套房",
        "rooms_subtitle": "每個細節都講究極致舒適",
        "rooms": [
            {
                "name": "經典客房",
                "description": "以手工家具與卡拉拉大理石衛浴打造寧靜優雅體驗。",
                "price": "每晚 EUR 450 起",
            },
            {
                "name": "主教堂套房",
                "description": "在私人露台獨享布魯內萊斯基圓頂的壯麗視野。",
                "price": "每晚 EUR 890 起",
            },
            {
                "name": "文藝復興套房",
                "description": "十六世紀原始壁畫與挑高天花，呈現皇室級住宿體驗。",
                "price": "每晚 EUR 1,200 起",
            },
        ],
        "view_details": "查看詳情",
        "amenities_title": "卓越設施",
        "amenities_subtitle": "為現代旅人精心策劃的體驗",
        "amenities": [
            {
                "icon": "restaurant",
                "name": "精緻早餐",
                "description": "每日供應佛羅倫斯傳統甜點與在地有機美食。",
            },
            {
                "icon": "deck",
                "name": "屋頂露台",
                "description": "在 360 度城市全景中品味招牌調酒。",
            },
            {
                "icon": "concierge",
                "name": "禮賓服務",
                "description": "專屬安排烏菲茲門票與托斯卡尼私人酒莊行程。",
            },
            {
                "icon": "spa",
                "name": "水療與養生",
                "description": "以古羅馬靈感打造的寧靜療癒空間與療程。",
            },
        ],
        "location_kicker": "周邊街區",
        "location_title": "佛羅倫斯之心",
        "location_text": "位於 ZTL 限行區內，鬧中取靜，步行即可抵達城市最具代表性的文化地標。",
        "landmarks": [
            {"name": "烏菲茲美術館", "distance": "穿越歷史廣場步行約 4 分鐘。"},
            {"name": "老橋", "distance": "步行約 6 分鐘即可抵達世界知名珠寶橋。"},
            {"name": "領主廣場", "distance": "距離飯店正門僅約 2 分鐘。"},
        ],
        "footer_text": "體驗佛羅倫斯奢華旅宿的最高境界。我們為追求非凡的旅人敞開大門。",
        "contact_title": "聯絡資訊",
        "quick_links_title": "快速連結",
        "quick_links": ["私人活動", "禮品券", "徵才", "媒體資料包"],
        "privacy": "隱私權",
        "terms": "條款",
        "copyright_suffix": "版權所有。",
        "language_label": "語言",
    },
}


@app.route("/")
def home():
    requested_lang = request.args.get("lang", "en").lower()
    current_lang = requested_lang if requested_lang in SUPPORTED_LANGUAGES else "en"
    t = TRANSLATIONS[current_lang]
    stats_values = ["1582", "24/7", "Michelin", "Duomo"]
    languages = [
        {"code": code, "label": data["label"]}
        for code, data in SUPPORTED_LANGUAGES.items()
    ]
    return render_template(
        "index.html",
        current_year=datetime.now().year,
        current_lang=current_lang,
        html_lang=SUPPORTED_LANGUAGES[current_lang]["html_lang"],
        languages=languages,
        stats_values=stats_values,
        t=t,
    )


if __name__ == "__main__":
    app.run(debug=True)
