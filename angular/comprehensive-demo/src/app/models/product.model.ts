/**
 * Product Model
 * 
 * Defines the structure of a Product entity in the application.
 * This model represents items that can be displayed, managed, and purchased.
 */

export interface Product {
  /**
   * Unique product identifier
   */
  id: number;

  /**
   * Product name/title
   */
  name: string;

  /**
   * Detailed product description
   */
  description: string;

  /**
   * Product price in the base currency (e.g., USD)
   * Stored as a number to allow for calculations
   */
  price: number;

  /**
   * Product category for organization and filtering
   */
  category: string;

  /**
   * URL to the product image
   * In a real application, this might be a path to an uploaded file
   */
  imageUrl?: string;

  /**
   * Stock quantity available
   * Used for inventory management
   */
  stock: number;

  /**
   * Whether the product is currently available for purchase
   */
  isAvailable: boolean;

  /**
   * Product rating (0-5 stars)
   * Calculated from user reviews
   */
  rating?: number;

  /**
   * Timestamp when the product was created
   */
  createdAt: string;

  /**
   * Timestamp when the product was last updated
   */
  updatedAt: string;
}

/**
 * Product Creation Data
 * 
 * Data structure for creating a new product.
 * Used in forms and API requests.
 */
export interface ProductCreate {
  name: string;
  description: string;
  price: number;
  category: string;
  imageUrl?: string;
  stock: number;
  isAvailable: boolean;
}

