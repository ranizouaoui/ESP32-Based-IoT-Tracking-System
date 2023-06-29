# Use an official Node.js runtime as a parent image
FROM node:14

# Set the working directory to /app
WORKDIR /app

# Copy package.json and package-lock.json to the working directory
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the rest of the app to the working directory
COPY . .

# Build the app
RUN npm run build

# Start the Vue.js app
CMD ["npm", "run", "serve"]