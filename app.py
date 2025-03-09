#app.py backend code
from flask import Flask, request, jsonify
from flask_cors import CORS
from pytrends.request import TrendReq

app = Flask(__name__)
CORS(app)  # Enable CORS for frontend-backend communication

pytrends = TrendReq(hl='en-US', tz=360)  # Initialize Google Trends API

@app.route('/search', methods=['GET'])
def search_product():
    product = request.args.get('query')
    if not product:
        return jsonify({'error': 'No product provided'}), 400

    print(f"Received search query: {product}")  # Debugging

    # Fetch Google Trends interest by region
    pytrends.build_payload([product], cat=0, timeframe='now 7-d', geo='', gprop='')
    interest_by_region = pytrends.interest_by_region()

    if interest_by_region.empty:
        print("No trends data found")  # Debugging
        return jsonify({'error': 'No data available'}), 404

    print("Google Trends data retrieved successfully!")  # Debugging

    # Convert DataFrame to dictionary
    demand_data = interest_by_region[product].to_dict()

    # Remove countries with zero demand
    filtered_demand = {country: score for country, score in demand_data.items() if score > 0}

    # Sort by highest demand and select top 20
    sorted_demand = dict(sorted(filtered_demand.items(), key=lambda item: item[1], reverse=True)[:20])

    return jsonify({'product': product, 'demand': sorted_demand})

if __name__ == '__main__':
    app.run(debug=True)